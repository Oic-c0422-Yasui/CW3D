#include "Enemy.h"
#include	"CameraController.h"

using namespace Sample;


CEnemy::CEnemy()

	: Sample::CActorObject()
	, m_Input()
	, m_DefaultPos(0,0,0)
{
	SetType(CHARA_ENEMY);
}

CEnemy::~CEnemy()
{
	Release();
}

bool CEnemy::Load(const EnemyBuildParameter& eneParam,
	const ActionCreatorPtr& actionCreator,
	const StateCreatorPtr& stateCreator,
	const ParameterCreatorPtr& paramCreator,
	const CharacterAICreatorPtr& aiCreator)
{
	//初期位置
	m_DefaultPos = eneParam.GetParam().m_Pos;

	//インプットキー
	auto& stateInput = std::make_shared<Sample::StateInput>();
	m_Input = stateInput;

	auto& enemy = eneParam.GetParam().m_Type;

	//メッシュ読み込み
	m_pMesh = Sample::ResourcePtrManager<CMeshContainer>::GetInstance().GetResource("Enemy", eneParam.GetParam().m_Type);
	if (m_pMesh == nullptr)
	{
		return false;
	}

	//モーション作成
	m_Motion = m_pMesh->CreateMotionController();
	//モーション状態設定
	m_Actor->SetAnimationState(m_Motion);

	//アクション作成
	actionCreator->Create(m_Actor);
	//ステート作成
	stateCreator->Create(m_StateMachine, m_Actor, m_Input);
	//パラメーター作成
	auto& param = m_Actor->GetParameterMap();
	paramCreator->Create(param);

	//パラメータ設定
	SettingParameter(param, eneParam.GetStatus());


	m_Position = m_DefaultPos;
	m_HPShowFlg = true;

	m_AI = aiCreator->Create(m_Actor, m_StateMachine, stateInput);

	return true;
}

void CEnemy::Initialize()
{
	m_Actor->SetPosition(m_DefaultPos);
	m_Actor->SetRotate(Vector3(0, MOF_ToDegree(90), 0));
	m_Actor->SetScale(Vector3(1, 1, 1));


	m_StateMachine->ChangeState(STATE_KEY_IDLE);
	matWorld = m_Actor->GetMatrix();
	m_ShowFlg = true;
	m_DeadFlg = false;
	m_HPShowFlg = true;

	//相手が獲得する必殺技ゲージの倍率
	SetUltBoostMag(1.0f);

	auto& gauge = m_Actor->GetParameterMap()->Get<Sample::ReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
	gauge = 0.0f;
	auto& hp = m_Actor->GetParameterMap()->Get<Sample::ReactiveParameter<int>>(PARAMETER_KEY_HP);
	hp = m_MaxHP.Get();
	m_HP = m_MaxHP.Get();
	auto& alpha = m_Actor->GetParameterMap()->Get<float>(PARAMETER_KEY_ALPHA);
	alpha = 1.0f;
	auto& invincible = m_Actor->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
	invincible = 0.0f;
}

void CEnemy::Update()
{
	if (!m_ShowFlg)
	{
		return;
	}
	
	m_Input->Update();

	auto& invincible = m_Actor->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
	if (invincible > 0.0f)
	{
		invincible -= CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
	}
	if (m_DeadFlg)
	{
		auto& alpha = m_Actor->GetParameterMap()->Get<float>(PARAMETER_KEY_ALPHA);
		if (alpha <= 0)
		{
			m_ShowFlg = false;
		}
	}
	m_AI->Update();
	Sample::CActorObject::Update();

	Vector3 pos = m_Actor->GetPosition();

	m_Position = m_Actor->GetPosition();
}

void CEnemy::Render()
{
	if (!m_ShowFlg)
	{
		return;
	}

	auto& alpha = m_Actor->GetParameterMap()->Get<float>(PARAMETER_KEY_ALPHA);
	m_Motion->RefreshBoneMatrix(matWorld);
	m_pMesh->Render(m_Motion, Vector4(1.0f, 1.0f, 1.0f, alpha));
}

void CEnemy::RenderDebug()
{
	CGraphicsUtilities::RenderBox(GetCollider(), Vector4(0, 1, 0, 0.2f));
}

void CEnemy::Render2D()
{
	if (!m_ShowFlg)
	{
		return;
	}

	
}

void CEnemy::Render2DDebug()
{
}

void CEnemy::Release()
{
	Sample::CActorObject::Release();
}

void CEnemy::Damage(const Vector3& direction, const Vector3& power,int damage,BYTE level)
{
	Sample::EffectCreateParameter param = { "DamageEffect1", Vector3(0, 1.0f, 0) , Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f),1.0f };
	Sample::EffectPtr effect = EffectControllerInstance.Play(param.name, GetCollider().Position, param);

	auto& hp = m_Actor->GetParameterMap()->Get<Sample::ReactiveParameter<int>>(PARAMETER_KEY_HP);
	auto& knockBack = m_Actor->GetParameterMap()->Get<Vector3>(PARAMETER_KEY_KNOCKBACK);

	auto& transform = m_Actor->GetTransform();
	transform->SetReverse(direction.x > 0 ? true : false);

	hp -= damage;
	if (hp <= 0)
	{
		hp = 0;

		m_DeadFlg = true;
		m_HPShowFlg = false;
	}
	m_HP = hp;

	if (m_Actor->GetArmorLevel() <= level)
	{
		knockBack = direction * power;

		CameraControllerInstance.Quake(0.20f, 40.0f, 0.2f);

		m_StateMachine->ChangeState(STATE_KEY_DAMAGE);
	}
}

bool CEnemy::IsInvincible() const
{
	auto& invincible = m_Actor->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
	return invincible > 0.0f || m_StateMachine->GetCurrentState()->GetKey() == STATE_KEY_DEAD || m_StateMachine->GetCurrentState()->GetKey() == STATE_KEY_DOWN;
}

void Sample::CEnemy::SettingParameter(const AnyParameterMapPtr& param, const EnemyStatusPtr& eneStatus)
{
	//HP
	auto& maxHP = param->Get<Sample::ReactiveParameter<int>>(PARAMETER_KEY_MAXHP);
	maxHP = eneStatus->m_Hp;
	auto& hp = param->Get<Sample::ReactiveParameter<int>>(PARAMETER_KEY_HP);
	hp = eneStatus->m_Hp;
	m_HP = maxHP;
	m_MaxHP = maxHP;
	//攻撃力
	auto& atk = param->Get<int>(PARAMETER_KEY_ATTACK);
	atk = eneStatus->m_Atk;
	//必殺技ゲージ
	auto& maxUltGauge = param->Get<ReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
	maxUltGauge = eneStatus->m_UltGauge;
	//当たり判定
	m_ColliderSize = eneStatus->m_ColliderSize;
	m_ColliderOffset = Vector3(0.0f,eneStatus->m_ColliderHeight, 0.0f);

}

