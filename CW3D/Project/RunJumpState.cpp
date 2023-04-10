#include "RunJumpState.h"

ActionGame::CRunJumpState::CRunJumpState()
	: CState()
{
}

void ActionGame::CRunJumpState::Start()
{
	action_ = Actor()->GetAction<CRunJumpAction>(GetKey());
	action_->Start();

}

void ActionGame::CRunJumpState::Execution()
{
	action_->Execution();
	// ������Ԃւ̈ڍs
	if (Actor()->GetVelocity()->GetVelocityY() <= 0.0f)
	{
		ChangeState(STATE_KEY_RUN_FALL);
	}
}

void ActionGame::CRunJumpState::InputExecution()
{
	float scale = TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());
	//�^�C���X�P�[����0�ȉ��̏ꍇ�A���͂��󂯕t���Ȃ�
	if (scale <= 0.0f)
	{
		return;
	}
	//���E�ňړ�

	if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) ||
		Input()->IsPress(INPUT_KEY_HORIZONTAL) ||
		Input()->IsNegativePress(INPUT_KEY_VERTICAL) ||
		Input()->IsPress(INPUT_KEY_VERTICAL))
	{
		action_->Acceleration(Input()->GetAxis(INPUT_KEY_HORIZONTAL), -(Input()->GetAxis(INPUT_KEY_VERTICAL)));
	}


	if (Input()->IsPush(INPUT_KEY_ATTACK))
	{
		ChangeState(STATE_KEY_RUN_JUMP_ATTACK1);
	}

	//�Ή������X�L���̃{�^����������Ă����炻�̃X�L���̃X�e�[�g�Ɉړ�
	for (int i = 0; i < Actor()->GetSkillController()->GetCount(); i++)
	{
		if (!Actor()->GetSkillController()->GetSkill(i)->CanUseSkill() || Actor()->GetSkillController()->GetSkill(i)->GetFlyState() == NULL)
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

void ActionGame::CRunJumpState::End()
{
}

void ActionGame::CRunJumpState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CRunJumpState::GetKey() const
{
	return STATE_KEY_RUN_JUMP;
}

