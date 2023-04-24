#include "LandingState.h"

ActionGame::CLandingState::CLandingState()
	: CBaseState()
{
}

void ActionGame::CLandingState::Start()
{
	action_ = Actor()->GetAction<CLandingAction>(GetKey());
	action_->Start();

}

void ActionGame::CLandingState::Execution() 
{
	action_->Execution();
	// ������Ԃւ̈ڍs
	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		ChangeState(STATE_KEY_IDLE);
	}
}

void ActionGame::CLandingState::InputExecution()
{
	//�^�C���X�P�[����0�ȉ��̏ꍇ�A���͂��󂯕t���Ȃ�
	if (IsTimeScaleZero())
	{
		return;
	}

	//���E�ňړ�
	if (IsPressMoveKey())
	{
		ChangeState(STATE_KEY_MOVE);
	}


	if (Input()->IsPush(INPUT_KEY_ATTACK))
	{
		ChangeState(STATE_KEY_ATTACK1);
	}

	//�Ή������X�L���̃{�^����������Ă����炻�̃X�L���̃X�e�[�g�Ɉړ�
	ChangeSkillState();

}

void ActionGame::CLandingState::End()
{
}

void ActionGame::CLandingState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CLandingState::GetKey() const
{
	return STATE_KEY_LANDING;
}
