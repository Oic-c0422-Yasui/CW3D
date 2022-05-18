#include "Player.h"

#include "ResourceManager.h"
#include "IdleState.h"
#include "MoveState.h"
#include "RunState.h"
#include "IdleMotionState.h"
#include "Attack1State.h"




CPlayer::CPlayer():
	m_Actor(std::make_shared<Sample::Actor>()),
	m_Move(),
	m_StateMachine(std::make_shared<Sample::StateMachine>()),
	m_pInput()
{
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

	m_Motion = m_pMesh->CreateMotionController();
	m_Actor->SetAnimationState(m_Motion);

	m_StateMachine = std::make_shared<Sample::StateMachine>();
	m_StateMachine->AddState(Sample::State::Create<Sample::IdleState>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::IdleMotionState>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::MoveState>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::RunState>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::Attack1State>(m_Actor, m_pInput));

	m_Move = Sample::Action::Create<Sample::MoveAction>();
	m_Actor->AddAction(m_Move);
	m_Actor->AddAction(Sample::Action::Create<Sample::IdleAction>());
	m_Actor->AddAction(Sample::Action::Create<Sample::IdleMotionAction>());
	m_Actor->AddAction(Sample::Action::Create<Sample::RunAction>());
	m_Actor->AddAction(Sample::Action::Create<Sample::Attack1Action>());


	return true;
}

void CPlayer::Initialize()
{
	m_Actor->SetPosition(Vector3(0, 0,0));
	m_Actor->SetRotate(Vector3(0, 0, 0));
	m_Actor->SetScale(Vector3(1, 1, 1));
	m_Move->Reset();

	m_StateMachine->ChangeState(STATE_KEY_IDLE);


	m_Speed = TEMP_SPEED;


	matWorld = m_Actor->GetMatrix();
}

void CPlayer::Update()
{
	//ステートのインプット
	m_StateMachine->InputExecution();
	//ステートの実行
	m_StateMachine->Execution();

	//移動の実行
	m_Actor->Update();
	//m_Move->Exection();

	//移動制限
	m_Actor->GetTransform()->ClipZ(-9.0f, 9.0f);
	m_Actor->GetTransform()->ClipY(0.0f, 50.0f);

	//マトリクスを取得
	matWorld = m_Actor->GetMatrix();

	m_Motion->AddTimer(CUtilities::GetFrameSecond());

}

void CPlayer::Render()
{
	m_Motion->RefreshBoneMatrix(matWorld);
	m_pMesh->Render(m_Motion);
}

void CPlayer::Release()
{
	MOF_SAFE_DELETE(m_Motion);
	m_pMesh.reset();
}


//bool CPlayer::Load(CMeshContainer* pMesh)
//{
//	m_pMesh = pMesh;
//	if (m_pMesh != nullptr)
//	{
//		return false;
//	}
//
//	return true;
//}
//
//void CPlayer::Initialize()
//{
//	m_Speed = TEMP_SPEED;
//	m_Position = Vector3(0, 0, 0);
//	m_Velocity = Vector3(0, 0, 0);
//	m_Rotation = Vector3(0, 0, 0);
//	m_Scale = Vector3(1, 1, 1);
//	CMatrix44 matRotate;
//	matRotate.RotationY(MOF_ToRadian(-60));
//	matWorld *= matRotate;
//}
//
//void CPlayer::Update()
//{
//	UpdateKey();
//	UpdateMove();
//	SetReverse();
//
//	m_Position += m_Velocity;
//}
//
//void CPlayer::Render()
//{
//
//	
//	matWorld.SetTranslation(m_Position);
//	m_pMesh->Render(matWorld);
//}
//
//void CPlayer::Release()
//{
//}
//
//void CPlayer::UpdateKey()
//{
//	m_HorizontalMoveFlg = false;
//	m_VerticalMoveFlg = false;
//	if (m_pInput->IsNegativePress(INPUT_KEY_HORIZONTAL))
//	{
//		m_HorizontalMoveFlg = true;
//		m_ReverseFlg = true;
//		m_Velocity.x -= m_Speed * (CUtilities::GetFrameSecond() * 10);
//		if (m_Velocity.x < -m_Speed)
//		{
//			m_Velocity.x = -m_Speed;
//		}
//	}
//	else if (m_pInput->IsPress(INPUT_KEY_HORIZONTAL))
//	{
//		m_HorizontalMoveFlg = true;
//		m_ReverseFlg = false;
//		m_Velocity.x += m_Speed * (CUtilities::GetFrameSecond() * 10);
//		if (m_Velocity.x > m_Speed)
//		{
//			m_Velocity.x = m_Speed;
//		}
//	}
//	if (m_pInput->IsNegativePress(INPUT_KEY_VERTICAL))
//	{
//		m_VerticalMoveFlg = true;
//		m_Velocity.z += m_Speed * (CUtilities::GetFrameSecond() * 10);
//		if (m_Velocity.z > m_Speed)
//		{
//			m_Velocity.z = m_Speed;
//		}
//	}
//	else if (m_pInput->IsPress(INPUT_KEY_VERTICAL))
//	{
//		m_VerticalMoveFlg = true;
//		m_Velocity.z -= m_Speed * (CUtilities::GetFrameSecond() * 10);
//		if (m_Velocity.z < -m_Speed)
//		{
//			m_Velocity.z = -m_Speed;
//		}
//	}
//}
//
//void CPlayer::UpdateMove()
//{
//	if (!m_HorizontalMoveFlg)
//	{
//		if (m_Velocity.x > 0)
//		{
//			m_Velocity.x -= m_Speed * (CUtilities::GetFrameSecond() * 10);
//			if (m_Velocity.x <= 0)
//			{
//				m_Velocity.x = 0;
//			}
//		}
//		else if (m_Velocity.x < 0)
//		{
//			m_Velocity.x += m_Speed * (CUtilities::GetFrameSecond() * 10);
//			if (m_Velocity.x >= 0)
//			{
//				m_Velocity.x = 0;
//			}
//		}
//	}
//	if (!m_VerticalMoveFlg)
//	{
//		if (m_Velocity.z > 0)
//		{
//			m_Velocity.z -= m_Speed * (CUtilities::GetFrameSecond() * 10);
//			if (m_Velocity.z <= 0)
//			{
//				m_Velocity.z = 0;
//			}
//		}
//		else if (m_Velocity.z < 0)
//		{
//			m_Velocity.z += m_Speed * (CUtilities::GetFrameSecond() * 10);
//			if (m_Velocity.z >= 0)
//			{
//				m_Velocity.z = 0;
//			}
//		}
//	}
//		
//	
//	
//}
//
//void CPlayer::SetReverse()
//{
//	if (m_ReverseFlg)
//	{
//		CMatrix44 matRotate;
//		matRotate.RotationY(MOF_ToRadian(60));
//		matWorld = matRotate;
//	}
//	else
//	{
//		CMatrix44 matRotate;
//		matRotate.RotationY(MOF_ToRadian(-60));
//		matWorld = matRotate;
//	}
//	
//}
