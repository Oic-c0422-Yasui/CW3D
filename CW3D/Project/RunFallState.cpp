#include "RunFallState.h"

ActionGame::RunFallState::RunFallState()
	: State()
{
}

void ActionGame::RunFallState::Start()
{
	m_FallAction = Actor()->GetAction<RunFallAction>(GetKey());
	m_FallAction->Start();

}

void ActionGame::RunFallState::Execution()
{
	m_FallAction->Execution();
	// ������Ԃւ̈ڍs
	if (Actor()->GetVelocity()->GetVelocityY() <= 0.0f &&
		Actor()->GetTransform()->GetPositionY() <= 0)
	{
		ChangeState(STATE_KEY_RUNLANDING);
	}
}

void ActionGame::RunFallState::InputExecution()
{
	//���E�ňړ�

	if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) ||
		Input()->IsPress(INPUT_KEY_HORIZONTAL) ||
		Input()->IsNegativePress(INPUT_KEY_VERTICAL) ||
		Input()->IsPress(INPUT_KEY_VERTICAL))
	{
		m_FallAction->Acceleration(Input()->GetAxis(INPUT_KEY_HORIZONTAL), -(Input()->GetAxis(INPUT_KEY_VERTICAL)));
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

void ActionGame::RunFallState::End()
{
}

void ActionGame::RunFallState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::RunFallState::GetKey() const
{
	return STATE_KEY_RUNFALL;
}
