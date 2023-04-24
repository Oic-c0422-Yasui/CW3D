#include "JumpState.h"

ActionGame::CJumpState::CJumpState()
	: CBaseState()
{
}

void ActionGame::CJumpState::Start()
{
	action_ = Actor()->GetAction<CJumpAction>(GetKey());
	action_->Start();

}

void ActionGame::CJumpState::Execution()
{
	action_->Execution();
	// ������Ԃւ̈ڍs
	if (Actor()->GetVelocity()->GetVelocityY() <= 0.0f)
	{
		ChangeState(STATE_KEY_FALL);
	}
}

void ActionGame::CJumpState::InputExecution()
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
		ChangeState(STATE_KEY_JUMP_ATTACK1);
	}

	//�Ή������X�L���̃{�^����������Ă����炻�̃X�L���̃X�e�[�g�Ɉړ�
	ChangeSkillState();

}

void ActionGame::CJumpState::End()
{
}

void ActionGame::CJumpState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CJumpState::GetKey() const
{
	return STATE_KEY_JUMP;
}
