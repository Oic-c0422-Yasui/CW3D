#include "Player.h"

#include "IdleState.h"
#include "MoveState.h"
#include "RunState.h"
#include "IdleMotionState.h"
#include "Attack1State.h"
#include "Attack2State.h"
#include "Attack3State.h"
#include "RunAttack1State.h"
#include "Skill1_1State.h"
#include "JumpState.h"
#include "FallState.h"
#include "LandingState.h"
#include "RunJumpState.h"
#include "RunFallState.h"
#include "RunLandingState.h"
#include "RunJumpAttack1State.h"
#include "RunJumpAttack2State.h"
#include "RunJumpAttack3State.h"
#include "JumpAttack1State.h"
#include "Skill2_1State.h"
#include "JumpSkill2_1State.h"
#include "Skill3_1State.h"
#include "JumpSkill3_1State.h"



CPlayer::CPlayer():
	Sample::CActorObject(),
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
	m_StateMachine->AddState(Sample::State::Create<Sample::JumpState>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::FallState>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::LandingState>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::RunJumpState>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::RunFallState>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::RunLandingState>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::Attack1State>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::Attack2State>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::Attack3State>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::JumpAttack1State>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::RunAttack1State>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::RunJumpAttack1State>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::RunJumpAttack2State>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::RunJumpAttack3State>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::Skill1_1State>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::Skill2_1State>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::JumpSkill2_1State>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::Skill3_1State>(m_Actor, m_pInput));
	m_StateMachine->AddState(Sample::State::Create<Sample::JumpSkill3_1State>(m_Actor, m_pInput));

	m_Actor->AddAction(Sample::Action::Create<Sample::MoveAction>());
	m_Actor->AddAction(Sample::Action::Create<Sample::IdleAction>());
	m_Actor->AddAction(Sample::Action::Create<Sample::IdleMotionAction>());
	m_Actor->AddAction(Sample::Action::Create<Sample::RunAction>());
	m_Actor->AddAction(Sample::Action::Create<Sample::JumpAction>());
	m_Actor->AddAction(Sample::Action::Create<Sample::FallAction>());
	m_Actor->AddAction(Sample::Action::Create<Sample::LandingAction>());
	m_Actor->AddAction(Sample::Action::Create<Sample::RunJumpAction>());
	m_Actor->AddAction(Sample::Action::Create<Sample::RunFallAction>());
	m_Actor->AddAction(Sample::Action::Create<Sample::RunLandingAction>());
	m_Actor->AddAction(Sample::Action::Create<Sample::Attack1Action>());
	m_Actor->AddAction(Sample::Action::Create<Sample::Attack2Action>());
	m_Actor->AddAction(Sample::Action::Create<Sample::Attack3Action>());
	m_Actor->AddAction(Sample::Action::Create<Sample::JumpAttack1Action>());
	m_Actor->AddAction(Sample::Action::Create<Sample::RunAttack1Action>());
	m_Actor->AddAction(Sample::Action::Create<Sample::RunJumpAttack1Action>());
	m_Actor->AddAction(Sample::Action::Create<Sample::RunJumpAttack2Action>());
	m_Actor->AddAction(Sample::Action::Create<Sample::RunJumpAttack3Action>());
	m_Actor->AddAction(Sample::Action::Create<Sample::Skill1_1Action>());
	m_Actor->AddAction(Sample::Action::Create<Sample::Skill2_1Action>());
	m_Actor->AddAction(Sample::Action::Create<Sample::JumpSkill2_1Action>());
	m_Actor->AddAction(Sample::Action::Create<Sample::Skill3_1Action>());
	m_Actor->AddAction(Sample::Action::Create<Sample::JumpSkill3_1Action>());

	m_Actor->GetParameterMap()->Add<int>(PARAMETER_KEY_HP, 500);
	m_Actor->GetParameterMap()->Add<int>(PARAMETER_KEY_DAMAGE, 0);
	m_Actor->GetParameterMap()->Add<int>(PARAMETER_KEY_ATTACK, 25);
	m_Actor->GetParameterMap()->Add<float>(PARAMETER_KEY_INVINCIBLE, 0.0f);

	Sample::SKillPtr skill;

	skill = m_Actor->GetSkillController()->Create(SKILL_KEY_1, INPUT_KEY_SKILL1, STATE_KEY_SKILL1_1, STATE_KEY_SKILL1_1);
	skill->SetSkillData(250, 5);


	skill = m_Actor->GetSkillController()->Create(SKILL_KEY_2, INPUT_KEY_SKILL2, STATE_KEY_SKILL2_1, STATE_KEY_JUMPSKILL2_1);
	skill->SetSkillData(120, 5);

	skill = m_Actor->GetSkillController()->Create(SKILL_KEY_3, INPUT_KEY_SKILL3, STATE_KEY_SKILL3_1, STATE_KEY_JUMPSKILL3_1);
	skill->SetSkillData(100, 5);

	return true;
}

void CPlayer::Initialize()
{
	m_ShowFlg = true;
	m_Actor->SetPosition(Vector3(0, 0,0));
	m_Actor->SetRotate(Vector3(0, 0, 0));
	m_Actor->SetScale(Vector3(1, 1, 1));

	m_StateMachine->ChangeState(STATE_KEY_IDLE);

	matWorld = m_Actor->GetMatrix();
}

void CPlayer::Update()
{
	if (!m_ShowFlg)
	{
		return;
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

void CPlayer::Release()
{
	Sample::CActorObject::Release();
}
