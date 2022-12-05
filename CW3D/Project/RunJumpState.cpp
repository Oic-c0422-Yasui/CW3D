#include "RunJumpState.h"

ActionGame::RunJumpState::RunJumpState()
	: State()
{
}

void ActionGame::RunJumpState::Start()
{
	m_JumpAction = Actor()->GetAction<RunJumpAction>(GetKey());
	m_JumpAction->Start();

}

void ActionGame::RunJumpState::Execution()
{
	m_JumpAction->Execution();
	// ������Ԃւ̈ڍs
	if (Actor()->GetVelocity()->GetVelocityY() <= 0.0f)
	{
		ChangeState(STATE_KEY_RUNFALL);
	}
}

void ActionGame::RunJumpState::InputExecution()
{
	//���E�ňړ�

	if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) ||
		Input()->IsPress(INPUT_KEY_HORIZONTAL) ||
		Input()->IsNegativePress(INPUT_KEY_VERTICAL) ||
		Input()->IsPress(INPUT_KEY_VERTICAL))
	{
		m_JumpAction->Acceleration(Input()->GetAxis(INPUT_KEY_HORIZONTAL), -(Input()->GetAxis(INPUT_KEY_VERTICAL)));
	}


	if (Input()->IsPush(INPUT_KEY_ATTACK))
	{
		ChangeState(STATE_KEY_RUNJUMPATTACK1);
	}

	//�Ή������X�L���̃{�^����������Ă����炻�̃X�L���̃X�e�[�g�Ɉړ�
	for (int i = 0; i < Actor()->GetSkillController()->GetCount(); i++)
	{
		if (!Actor()->GetSkillController()->GetSkill(i)->IsCanUse() || Actor()->GetSkillController()->GetSkill(i)->GetFlyState() == NULL)
		{
			continue;
		}
		if (Input()->IsPush(Actor()->GetSkillController()->GetSkill(i)->GetButton()))
		{

			Actor()->GetSkillController()->GetSkill(i)->Start();
			ChangeState(Actor()->GetSkillController()->GetSkill(i)->GetFlyState());
			break;
		}
	}

}

void ActionGame::RunJumpState::End()
{
}

void ActionGame::RunJumpState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::RunJumpState::GetKey() const
{
	return STATE_KEY_RUNJUMP;
}

