#include "Enemy.h"
#include	"CameraController.h"
#include	"EffectController.h"

using namespace ActionGame;


Enemy::Enemy()

	: ActionGame::ActorObject()
	, m_Input()
	, m_DefaultPos(0,0,0)
	, m_BossFlg(false)
{
	SetType(CHARA_TYPE::ENEMY);
}

Enemy::~Enemy()
{
	Release();
}

bool Enemy::Load(const EnemyBuildParameterPtr& eneParam,
	const ActionCreatorPtr& actionCreator,
	const StateCreatorPtr& stateCreator,
	const ParameterCreatorPtr& paramCreator,
	const CharacterAICreatorPtr& aiCreator)
{
	//初期位置
	m_DefaultPos = eneParam->GetParam().m_Pos;

	//ボスか判断
	m_BossFlg = eneParam->GetParam().m_IsBoss;

	//インプットキー
	auto& stateInput = std::make_shared<ActionGame::CStateInput>();
	m_Input = stateInput;

	//メッシュ取得
	m_pMesh = ActionGame::ResourcePtrManager<CMeshContainer>::GetInstance().GetResource("Enemy", eneParam->GetStatus()->MeshName);
	if (m_pMesh == nullptr)
	{
		return false;
	}

	//モーション作成
	m_Motion = m_pMesh->CreateMotionController();
	//モーション状態設定
	actor_->SetAnimationState(m_Motion);

	//アクション作成
	actionCreator->Create(actor_);
	//ステート作成
	stateCreator->Create(m_StateMachine, actor_, m_Input);
	//パラメーター作成
	auto& param = actor_->GetParameterMap();
	paramCreator->Create(param);

	//パラメータ設定
	SettingParameter(param, eneParam->GetStatus());


	//初期位置設定
	position_ = m_DefaultPos;

	//AI作成
	m_AI = aiCreator->Create(actor_, m_StateMachine, stateInput);

	return true;
}

void Enemy::Initialize()
{
	//パラメータ初期化
	auto param = actor_->GetParameterMap();
	auto& gauge = param->Get<ActionGame::ReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
	gauge = 0.0f;
	auto& hp = param->Get<ActionGame::ReactiveParameter<int>>(PARAMETER_KEY_HP);
	hp = m_MaxHP.Get();
	m_HP = m_MaxHP.Get();
	auto& alpha = param->Get<float>(PARAMETER_KEY_ALPHA);
	alpha = 1.0f;
	auto& invincible = param->Get<float>(PARAMETER_KEY_INVINCIBLE);
	invincible = 0.0f;
	auto& HPShowFlg = param->Get<ActionGame::ReactiveParameter<bool>>(PARAMETER_KEY_SHOW_HP);
	HPShowFlg = false;
	auto& armorLevel = param->Get<BYTE>(PARAMETER_KEY_ARMORLEVEL);
	armorLevel = param->Get<BYTE>(PARAMETER_KEY_DEFAULT_ARMORLEVEL);


	ActionGame::ActorObject::Initialize();
	//座標初期化
	actor_->SetPosition(m_DefaultPos);
	actor_->SetReverse(true);

	m_StateMachine->ChangeState(STATE_KEY_NPC_STARTPOSE);
	m_MatWorld = actor_->GetMatrix();
	m_ShowFlg = false;
	


}

void Enemy::Update()
{
	if (!m_ShowFlg)
	{
		return;
	}


	//無敵時間中なら時間を減らす
	auto& invincible = actor_->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
	if (invincible > 0.0f)
	{
		invincible -= CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
	}

	//死んだら
	if (m_DeadFlg)
	{
		//完全に透明になったら表示しない
		auto& alpha = actor_->GetParameterMap()->Get<float>(PARAMETER_KEY_ALPHA);
		if (alpha <= 0)
		{
			m_ShowFlg = false;
		}
	}

	//状態のインプット
	m_Input->Update();
	//AI更新
	m_AI->Update();

	ActionGame::ActorObject::Update();

	position_ = actor_->GetPosition();
}

void Enemy::Render()
{
	if (!m_ShowFlg)
	{
		return;
	}

	ActionGame::ActorObject::Render();
}

void Enemy::RenderDebug()
{
	CGraphicsUtilities::RenderBox(GetCollider(), Vector4(0, 1, 0, 0.2f));
}

void Enemy::Render2D()
{
	if (!m_ShowFlg)
	{
		return;
	}

	
}

void Enemy::Render2DDebug()
{
}

void Enemy::Release()
{
	ActionGame::ActorObject::Release();
}

void Enemy::Damage(const Vector3& direction, const Vector3& power,int damage,BYTE armorBrekeLevel)
{

	//ダメージエフェクト生成
	ActionGame::EffectCreateParameter param = { "DamageEffect1", Vector3(0, 1.0f, 0) , Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f),1.0f };
	ActionGame::EffectPtr effect = EffectControllerInstance.Play(param.name, GetCollider().Position, param);

	//ダメージを受けた方向に向く
	auto& transform = actor_->GetTransform();
	transform->SetReverse(direction.x > 0 ? true : false);

	//ダメージ
	auto& hp = actor_->GetParameterMap()->Get<ActionGame::ReactiveParameter<int>>(PARAMETER_KEY_HP);
	hp -= damage;

	//HPが０以下なら死亡
	if (hp <= 0)
	{
		hp = 0;

		m_DeadFlg = true;
		auto& HPShowFlg = actor_->GetParameterMap()->Get<ActionGame::ReactiveParameter<bool>>(PARAMETER_KEY_SHOW_HP);
		HPShowFlg = false;
	}
	m_HP = hp;

	//自身のアーマーレベルより相手のアーマー破壊レベルのほうが高いとき

	auto& armorLevel = actor_->GetParameterMap()->Get<BYTE>(PARAMETER_KEY_ARMORLEVEL);
	if (armorLevel <= armorBrekeLevel)
	{
		//ノックバック設定
		auto& knockBack = actor_->GetParameterMap()->Get<Vector3>(PARAMETER_KEY_KNOCKBACK);
		knockBack = direction * power;

		//カメラを揺らす
		CameraControllerInstance.Quake(0.20f, 40.0f, 0.2f);

		//ダメージステートへ遷移
		m_StateMachine->ChangeState(STATE_KEY_DAMAGE);
	}
}

bool Enemy::IsInvincible() const
{
	auto& invincible = actor_->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
	return invincible > 0.0f || m_StateMachine->GetCurrentState()->GetKey() == STATE_KEY_DEAD || m_StateMachine->GetCurrentState()->GetKey() == STATE_KEY_DOWN;
}

void ActionGame::Enemy::SettingParameter(const AnyParameterMapPtr& param, const EnemyStatusPtr& eneStatus)
{
	//HP
	auto& maxHP = param->Get<ActionGame::ReactiveParameter<int>>(PARAMETER_KEY_MAX_HP);
	maxHP = eneStatus->HP;
	auto& hp = param->Get<ActionGame::ReactiveParameter<int>>(PARAMETER_KEY_HP);
	hp = eneStatus->HP;
	m_HP = maxHP;
	m_MaxHP = maxHP;
	//攻撃力
	auto& atk = param->Get<int>(PARAMETER_KEY_ATTACK);
	atk = eneStatus->Atk;
	//名前
	m_Name = eneStatus->Name;
	//必殺技ゲージ
	auto& maxUltGauge = param->Get<ReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
	maxUltGauge = eneStatus->UltGauge;
	//相手が獲得する必殺技ゲージの倍率
	SetUltBoostMag(eneStatus->UltGaugeBoostMag);
	//重さ
	m_Weight = eneStatus->Weight;
	//アーマーレベル
	auto& defaultArmorLevel = param->Get<BYTE>(PARAMETER_KEY_DEFAULT_ARMORLEVEL);
	defaultArmorLevel = eneStatus->ArmorLevel;
	auto& armorLevel = param->Get<BYTE>(PARAMETER_KEY_ARMORLEVEL);
	armorLevel = eneStatus->ArmorLevel;
	//大きさ
	actor_->SetScale(eneStatus->Scale);
	//当たり判定
	m_ColliderSize = eneStatus->ColliderSize;
	m_ColliderOffset = Vector3(0.0f,eneStatus->ColliderHeight, 0.0f);

}

