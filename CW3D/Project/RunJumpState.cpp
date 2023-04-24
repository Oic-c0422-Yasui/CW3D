#include "RunJumpState.h"

ActionGame::CRunJumpState::CRunJumpState()
	: CBaseState()
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
	//�^�C���X�P�[����0�ȉ��̏ꍇ�A���͂��󂯕t���Ȃ�
	if (IsTimeScaleZero())
	{
		return;
	}
	//���E�ňړ�

	if (IsPressMoveKey())
	{
		action_->Acceleration(Input()->GetAxis(INPUT_KEY_HORIZONTAL), 
							-(Input()->GetAxis(INPUT_KEY_VERTICAL)));
	}


	if (Input()->IsPush(INPUT_KEY_ATTACK))
	{
		ChangeState(STATE_KEY_RUN_JUMP_ATTACK1);
	}

	//�Ή������X�L���̃{�^����������Ă����炻�̃X�L���̃X�e�[�g�Ɉړ�
	ChangeSkillState();

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

