#include "ActorObject.h"

using namespace ActionGame;


ActorObject::ActorObject()
	: m_Actor(std::make_shared<ActionGame::Actor>())
	, m_StateMachine(std::make_shared<ActionGame::StateMachine>())
	, m_Motion()
	, m_ShowFlg(false)
	, m_DeadFlg(false)
	, m_ColliderOffset(0,0,0)
	, m_ColliderSize(1, 1, 1)
	, m_UltBoostMag(0.0f)
{
	m_Actor->GetParameterMap()->Add<float>(PARAMETER_KEY_ALPHA, 1.0f);
	m_Actor->GetParameterMap()->Add<Vector3>(PARAMETER_KEY_KNOCKBACK, Vector3(0,0,0));
}

ActorObject::~ActorObject()
{
}

void ActionGame::ActorObject::Initialize()
{
	m_ShowFlg = true;
	m_DeadFlg = false;
	matWorld = m_Actor->GetMatrix();

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
	m_PrevPos = m_Actor->GetPosition();
	//移動の実行
	m_Actor->Update();

	//移動制限
	m_Actor->GetTransform()->ClipX(-36.0f, 132.0f);
	m_Actor->GetTransform()->ClipZ(-9.0f, 9.0f);
	m_Actor->GetTransform()->ClipY(0.0f, 50.0f);

	//マトリクスを取得
	matWorld = m_Actor->GetMatrix();

	m_Motion->AddTimer(CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale(m_Actor->GetType()));
}

void ActorObject::Render()
{
	if (!m_ShowFlg)
	{
		return;
	}
	auto& alpha = m_Actor->GetParameterMap()->Get<float>(PARAMETER_KEY_ALPHA);
	m_Motion->RefreshBoneMatrix(matWorld);
	m_pMesh->Render(m_Motion, Vector4(1.0f, 1.0f, 1.0f, alpha));
}

void ActorObject::Release()
{
	MOF_SAFE_DELETE(m_Motion);
	m_pMesh.reset();
}

void ActionGame::ActorObject::AddUltGauge(float gauge)
{
	auto& ult = m_Actor->GetParameterMap()->Get<ActionGame::ReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
	ult += gauge;
	auto& maxUlt = m_Actor->GetParameterMap()->Get<ActionGame::ReactiveParameter<float>>(PARAMETER_KEY_MAXULTGAUGE);
	ult = min(ult, maxUlt);
}
