#include "Enemy.h"
#include	"CameraController.h"
#include "ServiceLocator.h"
#include "ICombo.h"

using namespace ActionGame;


CEnemy::CEnemy()

	: ActionGame::CActorObject()
	, input_()
	, defaultPos_(0,0,0)
	, isBoss_(false)
{
	SetType(CHARA_TYPE::ENEMY);
}

CEnemy::~CEnemy()
{
	Release();
}

bool CEnemy::Load(const EnemyBuildParameterPtr& eneParam,
	const ActionCreatorPtr& actionCreator,
	const StateCreatorPtr& stateCreator,
	const ParameterCreatorPtr& paramCreator,
	const CharacterAICreatorPtr& aiCreator)
{
	//初期位置
	defaultPos_ = eneParam->GetParam().position_;

	//ボスか判断
	isBoss_ = eneParam->GetParam().isBoss_;
	if (isBoss_)
	{
		actor_->SetType(CHARA_TYPE::BOSS);
	}

	//インプットキー
	auto& stateInput = std::make_shared<Input::CStateInput>();
	input_ = stateInput;

	//メッシュ取得
	mesh_ = ResourcePtrManager<CMeshContainer>::GetInstance().GetResource("Enemy", eneParam->GetStatus()->MeshName);
	if (mesh_ == nullptr)
	{
		return false;
	}
	//シェーダー読み込み
	normalMap_ = ResourcePtrManager<MyClass::CNormalMapSkinnedParameter>::GetInstance().GetResource("Shader", "NormalMapSkin");

	//モーション作成
	motion_ = mesh_->CreateMotionController();
	//モーション状態設定
	actor_->SetAnimationState(motion_);

	//アクション作成
	actionCreator->Create(actor_);
	//ステート作成
	stateCreator->Create(stateMachine_, actor_, input_);
	//パラメーター作成
	auto& param = actor_->GetParameterMap();
	paramCreator->Create(param);

	//パラメータ設定
	SettingParameter(param, eneParam->GetStatus());


	//初期位置設定
	position_ = defaultPos_;

	//AI作成
	AI_ = aiCreator->Create(actor_, stateMachine_, stateInput);

	CActorObject::Load();

	return true;
}

void CEnemy::Initialize()
{
	//パラメータ初期化
	auto param = actor_->GetParameterMap();
	auto& gauge = param->Get<ActionGame::CReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
	gauge = 0.0f;
	auto& hp = param->Get<ActionGame::CReactiveParameter<int>>(PARAMETER_KEY_HP);
	hp = maxHP_.Get();
	HP_ = maxHP_.Get();
	auto& alpha = param->Get<float>(PARAMETER_KEY_ALPHA);
	alpha = 1.0f;
	auto& invincible = param->Get<float>(PARAMETER_KEY_INVINCIBLE_TIME);
	invincible = 0.0f;
	auto& isShowHP = param->Get<ActionGame::CReactiveParameter<bool>>(PARAMETER_KEY_SHOW_HP);
	isShowHP = false;
	auto& armorLevel = param->Get<BYTE>(PARAMETER_KEY_ARMORLEVEL);
	armorLevel = param->Get<BYTE>(PARAMETER_KEY_DEFAULT_ARMORLEVEL);


	ActionGame::CActorObject::Initialize();
	//座標初期化
	actor_->SetPosition(defaultPos_);
	actor_->SetReverse(true);

	stateMachine_->ChangeState(STATE_KEY_NPC_STARTPOSE);
	matWorld_ = actor_->GetMatrix();
	isShow_ = false;
	


}

void CEnemy::Update()
{
	if (!isShow_)
	{
		return;
	}


	//無敵時間中なら時間を減らす
	auto& invincible = actor_->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE_TIME);
	if (invincible > 0.0f)
	{
		invincible -= CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
	}

	//死んだら
	if (isDead_)
	{
		//完全に透明になったら表示しない
		auto& alpha = actor_->GetParameterMap()->Get<float>(PARAMETER_KEY_ALPHA);
		if (alpha <= 0)
		{
			isShow_ = false;
		}
	}

	//状態のインプット
	input_->Update();
	//AI更新
	AI_->Update();

	ActionGame::CActorObject::Update();

	position_ = actor_->GetPosition();
}

void CEnemy::Render()
{
	if (!isShow_)
	{
		return;
	}

	ActionGame::CActorObject::Render();
}

void CEnemy::RenderDebug()
{
	CGraphicsUtilities::RenderBox(GetCollider(), Vector4(0, 1, 0, 0.2f));
}

void CEnemy::Render2D()
{
	if (!isShow_)
	{
		return;
	}

	
}

void CEnemy::Render2DDebug()
{
}

void CEnemy::Release()
{
	ActionGame::CActorObject::Release();
}

void CEnemy::Damage(const Vector3& direction, const Vector3& power,int damage,BYTE armorBreakeLevel)
{

	//ダメージを受けた方向に向く
	auto& transform = actor_->GetTransform();
	transform->SetReverse(direction.x > 0 ? true : false);

	//ダメージ
	auto& hp = actor_->GetParameterMap()->Get<ActionGame::CReactiveParameter<int>>(PARAMETER_KEY_HP);
	hp -= damage;

	//コンボ数追加
	CServiceLocator<ICombo>::GetService()->AddCount();

	//カメラを揺らす
	CameraControllerInstance.Quake(0.25f, 40.0f, 0.2f);

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
		//HPをバー非表示
		auto& isShowHP = actor_->GetParameterMap()->Get<ActionGame::CReactiveParameter<bool>>(PARAMETER_KEY_SHOW_HP);
		isShowHP = false;
	}
	HP_ = hp;

}

void ActionGame::CEnemy::Damage(const Vector3& direction, const Vector3& power, int damage, BYTE armorBrakeLevel, const EffectCreateParameterPtr& effect)
{
	if (effect != nullptr)
	{
		//ダメージエフェクト生成
		EffectControllerInstance.Play(effect->name, GetCollider().Position, effect);
	}

	Damage(direction,power,damage,armorBrakeLevel);
}

bool CEnemy::IsInvincible() const
{
	auto& invincible = actor_->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE_TIME);
	return invincible > 0.0f || stateMachine_->GetCurrentState()->GetKey() == STATE_KEY_DEAD || stateMachine_->GetCurrentState()->GetKey() == STATE_KEY_DOWN;
}

void ActionGame::CEnemy::SettingParameter(const AnyParameterMapPtr& param, const EnemyStatusPtr& eneStatus)
{
	//HP
	auto& maxHP = param->Get<ActionGame::CReactiveParameter<int>>(PARAMETER_KEY_MAX_HP);
	maxHP = eneStatus->HP;
	auto& hp = param->Get<ActionGame::CReactiveParameter<int>>(PARAMETER_KEY_HP);
	hp = eneStatus->HP;
	HP_ = maxHP;
	maxHP_ = maxHP;
	//攻撃力
	auto& atk = param->Get<int>(PARAMETER_KEY_ATTACK);
	atk = eneStatus->Atk;
	//名前
	name_ = eneStatus->Name;
	//必殺技ゲージ
	auto& maxUltGauge = param->Get<CReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
	maxUltGauge = eneStatus->UltGauge;
	//相手が獲得する必殺技ゲージの倍率
	SetUltBoostMag(eneStatus->UltGaugeBoostMag);
	//重さ
	weight_ = eneStatus->Weight;
	//アーマーレベル
	auto& defaultArmorLevel = param->Get<BYTE>(PARAMETER_KEY_DEFAULT_ARMORLEVEL);
	defaultArmorLevel = eneStatus->ArmorLevel;
	auto& armorLevel = param->Get<BYTE>(PARAMETER_KEY_ARMORLEVEL);
	armorLevel = eneStatus->ArmorLevel;
	//大きさ
	actor_->SetScale(eneStatus->Scale);
	//当たり判定
	colliderSize_ = eneStatus->ColliderSize;
	colliderOffset_ = Vector3(0.0f,eneStatus->ColliderHeight, 0.0f);

}

