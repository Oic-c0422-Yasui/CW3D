#include "IdleMotionState.h"

ActionGame::CIdleMotionState::CIdleMotionState()
	: CBaseState()
{
}

void ActionGame::CIdleMotionState::Start()
{
	action_ = Actor()->GetAction<IdleMotionAction>(GetKey());
	action_->Start();

}

void ActionGame::CIdleMotionState::Execution()
{
	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		ChangeState(STATE_KEY_IDLE);
	}
}

void ActionGame::CIdleMotionState::InputExecution()
{
	//�^�C���X�P�[����0�ȉ��̏ꍇ�A���͂��󂯕t���Ȃ�
	if (IsTimeScaleZero())
	{
		return;
	}

	//�L�[�{�[�h�ł̈ړ�
	if (IsPressMoveKey())
	{
		ChangeState(STATE_KEY_MOVE);
	}

	if (Input()->IsPush(INPUT_KEY_JUMP))
	{
		ChangeState(STATE_KEY_JUMP);
	}

	if (Input()->IsPush(INPUT_KEY_ATTACK))
	{
		ChangeState(STATE_KEY_ATTACK1);
	}

	
	//�Ή������X�L���̃{�^����������Ă����炻�̃X�L���̃X�e�[�g�Ɉړ�
	ChangeSkillState();
}

void ActionGame::CIdleMotionState::End()
{
}

void ActionGame::CIdleMotionState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CIdleMotionState::GetKey() const
{
	return STATE_KEY_IDLE_MOTION;
}
