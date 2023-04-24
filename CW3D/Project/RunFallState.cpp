#include "RunFallState.h"

ActionGame::CRunFallState::CRunFallState()
	: CBaseState()
{
}

void ActionGame::CRunFallState::Start()
{
	action_ = Actor()->GetAction<CRunFallAction>(GetKey());
	action_->Start();

}

void ActionGame::CRunFallState::Execution()
{
	action_->Execution();
	// ���n��Ԃւ̈ڍs
	if (!IsFly())
	{
		ChangeState(STATE_KEY_RUN_LANDING);
	}
}

void ActionGame::CRunFallState::InputExecution()
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

void ActionGame::CRunFallState::End()
{
}

void ActionGame::CRunFallState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CRunFallState::GetKey() const
{
	return STATE_KEY_RUN_FALL;
}
