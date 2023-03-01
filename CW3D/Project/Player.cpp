#include "Player.h"

using namespace ActionGame;

ActionGame::CPlayer::CPlayer()
	: ActionGame::CActorObject()
	, input_()

{
	SetType(CHARA_TYPE::PLAYER);
}

ActionGame::CPlayer::~CPlayer()
{
}

bool ActionGame::CPlayer::Load()
{
	//メッシュ取得
	mesh_ = ResourcePtrManager<CMeshContainer>::GetInstance().GetResource("Player", "Player");

	if (mesh_ == nullptr)
	{
		return false;
	}
	//モーション読み込み
	motion_ = mesh_->CreateMotionController();
	actor_->SetAnimationState(motion_);
	
	stateMachine_ = std::make_shared<ActionGame::StateMachine>();
	//アクション作成
	actionCreator_.Create(actor_);
	//ステート作成
	stateCreator_.Create(stateMachine_, actor_, input_);
	
	//パラメーター作成
	auto& param = actor_->GetParameterMap();
	parameterCreator_.Create(param);
	//パラメーター設定
	maxHP_ = param->Get<ActionGame::CReactiveParameter<int>>(PARAMETER_KEY_MAX_HP);
	maxUltGauge_ = param->Get<ActionGame::CReactiveParameter<float>>(PARAMETER_KEY_MAX_ULTGAUGE);
	//スキル設定
	skillCreator_.Create(actor_);
	
	return true;
}

void ActionGame::CPlayer::Initialize()
{
	//座標設定
	actor_->SetPosition(Vector3(-30, 0,0));
	actor_->SetRotate(Vector3(0, MOF_ToRadian(-90), 0));
	actor_->SetScale(Vector3(1, 1, 1));
	colliderSize_ = Vector3(0.5f, 0.8f, 0.5f);
	colliderOffset_.y = 1.0f;
	escapeColliderSize_ = colliderSize_ + Vector3(1.2f,0.5f,1.2f);
	actor_->SetReverse(false);

	//初期は待機モーション
	stateMachine_->ChangeState(STATE_KEY_STARTPOSE);

	//相手が獲得する必殺技ゲージの倍率
	SetUltBoostMag(1.0f);

	//パラメータ初期化
	auto param = actor_->GetParameterMap();
	auto& gauge = param->Get<ActionGame::CReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
	gauge = 0.0f;
	auto& hp = param->Get<ActionGame::CReactiveParameter<int>>(PARAMETER_KEY_HP);
	hp = maxHP_.Get();
	auto& alpha = param->Get<float>(PARAMETER_KEY_ALPHA);
	alpha = 1.0f;
	auto& invincible = param->Get<float>(PARAMETER_KEY_INVINCIBLE);
	invincible = 0.0f;
	auto& armorLevel = param->Get<BYTE>(PARAMETER_KEY_ARMORLEVEL);
	armorLevel = param->Get<BYTE>(PARAMETER_KEY_DEFAULT_ARMORLEVEL);

	//スキル初期化
	actor_->GetSkillController()->Reset();
	
	CActorObject::Initialize();
}

void ActionGame::CPlayer::Update()
{
	if (!isShow_)
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
	if (isDead_)
	{
		//完全に透明なら表示しない
		auto& alpha = actor_->GetParameterMap()->Get<float>(PARAMETER_KEY_ALPHA);
		if (alpha <= 0)
		{
			isShow_ = false;
		}
	}
	ActionGame::CActorObject::Update();
}

void ActionGame::CPlayer::Render()
{
	if (!isShow_)
	{
		return;
	}
	ActionGame::CActorObject::Render();
}

void ActionGame::CPlayer::RenderDebug2D()
{

}

void ActionGame::CPlayer::Release()
{
	ActionGame::CActorObject::Release();
}

void ActionGame::CPlayer::Damage(const Vector3& direction, const Vector3& power, int damage,BYTE armorBreakeLevel)
{

	//ダメージを受けた方向に向く
	auto& transform = actor_->GetTransform();
	transform->SetReverse(direction.x > 0 ? true : false);


	//ダメージ
	auto& hp = actor_->GetParameterMap()->Get<ActionGame::CReactiveParameter<int>>(PARAMETER_KEY_HP);
	hp -= damage;

	//必殺技ゲージ獲得
	AddUltGauge(1.0f);

	//自身のアーマーレベルより相手のアーマー破壊レベルのほうが高いとき
	auto& armorLevel = actor_->GetParameterMap()->Get<BYTE>(PARAMETER_KEY_ARMORLEVEL);
	if (armorLevel <= armorBreakeLevel)
	{
		//ノックバック設定
		auto& knockBack = actor_->GetParameterMap()->Get<Vector3>(PARAMETER_KEY_KNOCKBACK);
		knockBack = direction * power;

		//ダメージステートへ遷移
		stateMachine_->ChangeState(STATE_KEY_DAMAGE);
	}

	//HPが０以下なら死亡
	if (hp <= 0)
	{
		//死亡時のみ、アーマーレベルが相手より高くてもステートを遷移
		if (armorLevel > armorBreakeLevel)
		{
			//ダメージステートへ遷移
			stateMachine_->ChangeState(STATE_KEY_DAMAGE);
		}
		hp = 0;
		isDead_ = true;
	}

}

void ActionGame::CPlayer::Damage(const Vector3& direction, const Vector3& power, int damage, BYTE armorBrakeLevel, const EffectCreateParameterPtr& effect)
{
	if (effect != nullptr)
	{
		//ダメージエフェクト生成
		EffectControllerInstance.Play(effect->name, GetCollider().Position, effect);
	}

	Damage(direction, power, damage, armorBrakeLevel);
}

bool ActionGame::CPlayer::IsInvincible() const
{
	auto& invincible = actor_->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
	return invincible > 0.0f || stateMachine_->GetCurrentState()->GetKey() == STATE_KEY_DEAD || stateMachine_->GetCurrentState()->GetKey() == STATE_KEY_DOWN
							|| stateMachine_->GetCurrentState()->GetKey() == STATE_KEY_STARTPOSE;
}

void ActionGame::CPlayer::ClearPose()
{
	if (!stateMachine_->IsState(STATE_KEY_CLEARPOSE))
	{
		stateMachine_->ChangeState(STATE_KEY_CLEARPOSE);
	}
}
