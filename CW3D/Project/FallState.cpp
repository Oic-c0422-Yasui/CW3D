#include "FallState.h"

ActionGame::CFallState::CFallState()
	: CBaseState()
{
}

void ActionGame::CFallState::Start() 
{
	action_ = Actor()->GetAction<CFallAction>(GetKey());
	action_->Start();

}

void ActionGame::CFallState::Execution()
{
	action_->Execution();
	// ���n��Ԃւ̈ڍs
	if (!IsFly())
	{
		ChangeState(STATE_KEY_LANDING);
	}
}

void ActionGame::CFallState::InputExecution()
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

void ActionGame::CFallState::End()
{
}

void ActionGame::CFallState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CFallState::GetKey() const
{
	return STATE_KEY_FALL;
}