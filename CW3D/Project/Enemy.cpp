#include "Enemy.h"

#include "ResourceManager.h"
#include "IdleState.h"
#include "MoveState.h"
#include "RunState.h"
#include "IdleMotionState.h"
#include "Attack1State.h"
#include "StateInput.h"

CEnemy::CEnemy()
	: m_Actor(std::make_shared<Sample::Actor>())
	, m_StateMachine(std::make_shared<Sample::StateMachine>())
	,m_Input()
{
}

CEnemy::~CEnemy()
{
	Release();
}

bool CEnemy::Load()
{
	m_Input = std::make_shared<Sample::StateInput>();

	m_pMesh = Sample::ResourceManager<CMeshContainer>::GetInstance().GetResource("Zombie");

	if (m_pMesh == nullptr)
	{
		return false;
	}

	m_Motion = m_pMesh->CreateMotionController();
	m_Actor->SetAnimationState(m_Motion);

	m_StateMachine = std::make_shared<Sample::StateMachine>();
	m_StateMachine->AddState(Sample::State::Create<Sample::IdleState>(m_Actor, m_Input));
	m_StateMachine->AddState(Sample::State::Create<Sample::IdleMotionState>(m_Actor, m_Input));
	m_StateMachine->AddState(Sample::State::Create<Sample::MoveState>(m_Actor, m_Input));
	m_StateMachine->AddState(Sample::State::Create<Sample::RunState>(m_Actor, m_Input));
	m_StateMachine->AddState(Sample::State::Create<Sample::Attack1State>(m_Actor, m_Input));

	m_Actor->AddAction(Sample::Action::Create<Sample::IdleAction>());
	m_Actor->AddAction(Sample::Action::Create<Sample::MoveAction>());
	m_Actor->AddAction(Sample::Action::Create<Sample::IdleMotionAction>());
	m_Actor->AddAction(Sample::Action::Create<Sample::RunAction>());
	m_Actor->AddAction(Sample::Action::Create<Sample::Attack1Action>());



	return true;
}

void CEnemy::Initialize(CVector3 pos)
{
	m_Actor->SetPosition(pos);
	m_Actor->SetRotate(Vector3(0, 0, 0));
	m_Actor->SetScale(Vector3(1, 1, 1));

	m_StateMachine->ChangeState(STATE_KEY_IDLE);

	matWorld = m_Actor->GetMatrix();


}

void CEnemy::Update()
{
	//�X�e�[�g�̃C���v�b�g
	m_StateMachine->InputExecution();
	//�X�e�[�g�̎��s
	m_StateMachine->Execution();

	//�ړ��̎��s
	m_Actor->Update();
	//m_Move->Exection();

	//�ړ�����
	m_Actor->GetTransform()->ClipZ(-9.0f, 9.0f);
	m_Actor->GetTransform()->ClipY(0.0f, 50.0f);

	//�}�g���N�X���擾
	matWorld = m_Actor->GetMatrix();

	m_Motion->AddTimer(CUtilities::GetFrameSecond());
}

void CEnemy::Render()
{
	m_Motion->RefreshBoneMatrix(matWorld);
	m_pMesh->Render(m_Motion);
}

void CEnemy::RenderDebug()
{
}

void CEnemy::Release()
{
	MOF_SAFE_DELETE(m_Motion);
	m_pMesh.reset();
}
