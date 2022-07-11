#include "Player.h"




CPlayer::CPlayer()
	: Sample::CActorObject()
	, m_pInput()


{
	SetType(CHARA_PLAYER);
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Load()
{
	m_pMesh = Sample::ResourceManager<CMeshContainer>::GetInstance().GetResource("Player");

	if (m_pMesh == nullptr)
	{
		return false;
	}
	//モーション読み込み
	m_Motion = m_pMesh->CreateMotionController();
	m_Actor->SetAnimationState(m_Motion);
	
	m_StateMachine = std::make_shared<Sample::StateMachine>();
	//アクション作成
	m_ActionCreator.Create(m_Actor);
	//ステート作成
	m_StateCreator.Create(m_StateMachine, m_Actor, m_pInput);
	
	//パラメーター作成
	auto& param = m_Actor->GetParameterMap();
	m_ParameterCreator.Create(param);
	//パラメーター設定
	m_MaxHP = param->Get<Sample::ReactiveParameter<int>>(PARAMETER_KEY_MAXHP);
	m_MaxUltGauge = param->Get<Sample::ReactiveParameter<float>>(PARAMETER_KEY_MAXULTGAUGE);
	//スキル設定
	m_SkillCreator.Create(m_Actor);
	
	return true;
}

void CPlayer::Initialize()
{
	m_ShowFlg = true;
	m_DeadFlg = false;
	m_Actor->SetPosition(Vector3(-30, 0,0));
	m_Actor->SetRotate(Vector3(0, 0, 0));
	m_Actor->SetScale(Vector3(1, 1, 1));
	m_ColliderSize = Vector3(0.5f, 0.8f, 0.5f);
	m_ColliderOffset.y = 1.0f;
	m_EscapeColliderSize = m_ColliderSize + Vector3(1.2f,0.5f,1.2f);

	m_StateMachine->ChangeState(STATE_KEY_IDLE);

	matWorld = m_Actor->GetMatrix();
	//相手が獲得する必殺技ゲージの倍率
	SetUltBoostMag(1.0f);
	//ゲージ初期化
	auto& gauge = m_Actor->GetParameterMap()->Get<Sample::ReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
	gauge = 0.0f;
	auto& hp = m_Actor->GetParameterMap()->Get<Sample::ReactiveParameter<int>>(PARAMETER_KEY_HP);
	hp = m_MaxHP.Get();
	auto& alpha = m_Actor->GetParameterMap()->Get<float>(PARAMETER_KEY_ALPHA);
	alpha = 1.0f;
	auto& invincible = m_Actor->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
	invincible = 0.0f;

	m_Actor->GetSkillController()->Reset();
}

void CPlayer::Update()
{
	if (!m_ShowFlg)
	{
		return;
	}
	auto& invincible = m_Actor->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
	if (invincible > 0.0f)
	{
		invincible -= CUtilities::GetFrameSecond() * TimeControllerInstance.GetTimeScale();
	}
	if (m_DeadFlg)
	{
		auto& alpha = m_Actor->GetParameterMap()->Get<float>(PARAMETER_KEY_ALPHA);
		if (alpha <= 0)
		{
			m_ShowFlg = false;
		}
	}
	Sample::CActorObject::Update();
}

void CPlayer::Render()
{
	if (!m_ShowFlg)
	{
		return;
	}
	Sample::CActorObject::Render();
}

void CPlayer::RenderDebug2D()
{
	CGraphicsUtilities::RenderString(400, 20, "ARMLv:", m_Actor->GetArmorLevel());
}

void CPlayer::Release()
{
	Sample::CActorObject::Release();
}

void CPlayer::Damage(const Vector3& direction, Vector3 power, int damage,BYTE level)
{
	Sample::EffectCreateParameter param = { "DamageEffect1", Vector3(0, 1.0f, 0) , Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f),1.0f };
	Sample::EffectPtr effect = EffectControllerInstance.Play(param.name, GetCollider().Position, param);

	auto& knockBack = m_Actor->GetParameterMap()->Get<Vector3>(PARAMETER_KEY_KNOCKBACK);

	auto& transform = m_Actor->GetTransform();
	transform->SetReverse(direction.x > 0 ? true : false);

	auto& hp = m_Actor->GetParameterMap()->Get<Sample::ReactiveParameter<int>>(PARAMETER_KEY_HP);
	hp -= damage;

	//必殺技ゲージ獲得
	AddUltGauge(1.0f);

	if (hp <= 0)
	{
		hp = 0;

		m_DeadFlg = true;
	}

	if (m_Actor->GetArmorLevel() <= level)
	{
		knockBack = direction * power;

		m_StateMachine->ChangeState(STATE_KEY_DAMAGE);
	}

}

bool CPlayer::IsInvincible() const
{
	auto& invincible = m_Actor->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
	return invincible > 0.0f || m_StateMachine->GetCurrentState()->GetKey() == STATE_KEY_DEAD || m_StateMachine->GetCurrentState()->GetKey() == STATE_KEY_DOWN;
}

void CPlayer::SetClearPose()
{
	if (!m_StateMachine->IsState(STATE_KEY_CLEARPOSE))
	{
		m_StateMachine->ChangeState(STATE_KEY_CLEARPOSE);
	}
}
