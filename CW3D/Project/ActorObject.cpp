#include "ActorObject.h"
#include "ResourceManager.h"

using namespace ActionGame;


CActorObject::CActorObject()
	: actor_(std::make_shared<ActionGame::Actor>())
	, stateMachine_(std::make_shared<ActionGame::StateMachine>())
	, motion_()
	, isShow_(false)
	, isDead_(false)
	, colliderOffset_(0,0,0)
	, colliderSize_(1, 1, 1)
	, ultBoostMag_(0.0f)
	, weight_(50.0f)
	, normalMap_(nullptr)
	, matWorld_()
	, shadow_()
{
	actor_->GetParameterMap()->Add<float>(PARAMETER_KEY_ALPHA, 1.0f);
	actor_->GetParameterMap()->Add<Vector3>(PARAMETER_KEY_KNOCKBACK, Vector3(0,0,0));
	actor_->GetParameterMap()->Add<bool>(PARAMETER_KEY_THROUGH_COLLISION, false);
}

CActorObject::~CActorObject()
{
}

bool ActionGame::CActorObject::Load()
{
	if (!shadow_.Load())
	{
		return false;
	}

	return true;
}

void ActionGame::CActorObject::Initialize()
{
	isShow_ = true;
	isDead_ = false;
	matWorld_ = actor_->GetMatrix();
	const int hipBoneNum = 1;
	auto bone = motion_->GetBoneState(hipBoneNum);
	shadow_.Initialize(bone,actor_->GetTransform()->GetScale());

	stateMachine_->SetUp();
}

void CActorObject::Update()
{
	if (!isShow_)
	{
		return;
	}

	//ステートのインプット
	stateMachine_->InputExecution();
	//ステートの実行
	stateMachine_->Execution();
	prevPosision_ = actor_->GetPosition();
	//移動の実行
	actor_->Update();

	//移動制限
	actor_->GetTransform()->ClipX(-36.0f, 132.0f);
	actor_->GetTransform()->ClipZ(-9.0f, 9.0f);
	actor_->GetTransform()->ClipY(0.0f, 50.0f);

	//マトリクスを取得
	matWorld_ = actor_->GetMatrix();
	
	//影の座標移動
	const int hipBoneNum = 1;
	auto bone = motion_->GetBoneState(hipBoneNum);
	shadow_.Update(bone,actor_->GetPosition());
	
	//モーションのタイマーを進める
	motion_->AddTimer(CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale(actor_->GetType()));
}

void CActorObject::Render()
{
	if (!isShow_)
	{
		return;
	}
	auto& alpha = actor_->GetParameterMap()->Get<float>(PARAMETER_KEY_ALPHA);
	motion_->RefreshBoneMatrix(matWorld_);
	mesh_->Render(motion_, Vector4(1.0f, 1.0f, 1.0f, alpha),
		normalMap_->GetShader().get(), normalMap_->GetShaderBind().get());

	shadow_.Render(Vector4(1.0f, 1.0f, 1.0f, alpha));
}

void CActorObject::Release()
{
	MOF_SAFE_DELETE(motion_);
	mesh_.reset();
	shadow_.Release();
}

void ActionGame::CActorObject::AddUltGauge(float gauge)
{
	auto& ult = actor_->GetParameterMap()->Get<ActionGame::CReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
	ult += gauge;
	auto& maxUlt = actor_->GetParameterMap()->Get<ActionGame::CReactiveParameter<float>>(PARAMETER_KEY_MAX_ULTGAUGE);
	ult = min(ult, maxUlt);
}

bool ActionGame::CActorObject::IsThroughCollision() const noexcept
{
	auto param = actor_->GetParameterMap();

	return param->Get<bool>(PARAMETER_KEY_THROUGH_COLLISION);
}
