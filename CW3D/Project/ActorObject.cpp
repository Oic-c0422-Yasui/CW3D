#include "ActorObject.h"

using namespace ActionGame;


ActorObject::ActorObject()
	: actor_(std::make_shared<ActionGame::Actor>())
	, m_StateMachine(std::make_shared<ActionGame::StateMachine>())
	, m_Motion()
	, m_ShowFlg(false)
	, m_DeadFlg(false)
	, m_ColliderOffset(0,0,0)
	, m_ColliderSize(1, 1, 1)
	, m_UltBoostMag(0.0f)
	, m_Weight(50.0f)
{
	actor_->GetParameterMap()->Add<float>(PARAMETER_KEY_ALPHA, 1.0f);
	actor_->GetParameterMap()->Add<Vector3>(PARAMETER_KEY_KNOCKBACK, Vector3(0,0,0));
	actor_->GetParameterMap()->Add<bool>(PARAMETER_KEY_THROUGH_COLLISION, false);
}

ActorObject::~ActorObject()
{
}

void ActionGame::ActorObject::Initialize()
{
	m_ShowFlg = true;
	m_DeadFlg = false;
	m_MatWorld = actor_->GetMatrix();

	m_StateMachine->SetUp();
}

void ActorObject::Update()
{
	if (!m_ShowFlg)
	{
		return;
	}

	//ステートのインプット
	m_StateMachine->InputExecution();
	//ステートの実行
	m_StateMachine->Execution();
	m_PrevPos = actor_->GetPosition();
	//移動の実行
	actor_->Update();

	//移動制限
	actor_->GetTransform()->ClipX(-36.0f, 132.0f);
	actor_->GetTransform()->ClipZ(-9.0f, 9.0f);
	actor_->GetTransform()->ClipY(0.0f, 50.0f);

	//マトリクスを取得
	m_MatWorld = actor_->GetMatrix();

	m_Motion->AddTimer(CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale(actor_->GetType()));
}

void ActorObject::Render()
{
	if (!m_ShowFlg)
	{
		return;
	}
	auto& alpha = actor_->GetParameterMap()->Get<float>(PARAMETER_KEY_ALPHA);
	m_Motion->RefreshBoneMatrix(m_MatWorld);
	m_pMesh->Render(m_Motion, Vector4(1.0f, 1.0f, 1.0f, alpha));
}

void ActorObject::Release()
{
	MOF_SAFE_DELETE(m_Motion);
	m_pMesh.reset();
}

void ActionGame::ActorObject::AddUltGauge(float gauge)
{
	auto& ult = actor_->GetParameterMap()->Get<ActionGame::ReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
	ult += gauge;
	auto& maxUlt = actor_->GetParameterMap()->Get<ActionGame::ReactiveParameter<float>>(PARAMETER_KEY_MAX_ULTGAUGE);
	ult = min(ult, maxUlt);
}

bool ActionGame::ActorObject::IsThroughCollision() const noexcept
{
	auto param = actor_->GetParameterMap();

	return param->Get<bool>(PARAMETER_KEY_THROUGH_COLLISION);
}
