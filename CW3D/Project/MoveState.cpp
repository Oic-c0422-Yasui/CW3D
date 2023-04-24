#include "MoveState.h"

ActionGame::CMoveState::CMoveState()
	: CBaseState()
{
}

void ActionGame::CMoveState::Start()
{
	action_ = Actor()->GetAction<CMoveAction>(STATE_KEY_MOVE);
	if (Input()->IsPress(INPUT_KEY_HORIZONTAL))
	{
		Actor()->SetReverse(false);
	}
	else if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL))
	{
		Actor()->SetReverse(true);
	}
	action_->Start();

}

void ActionGame::CMoveState::Execution()
{
	action_->Execution();
}

void ActionGame::CMoveState::InputExecution()
{
	//�^�C���X�P�[����0�ȉ��̏ꍇ�A���͂��󂯕t���Ȃ�
	if (IsTimeScaleZero())
	{
		return;
	}

	InputDash();

	//���E�ňړ�
	if (IsPressMoveKey())
	{
		action_->Acceleration(Input()->GetAxis(INPUT_KEY_HORIZONTAL), 
							-(Input()->GetAxis(INPUT_KEY_VERTICAL)));
	}
	else
	{
		ChangeState(STATE_KEY_IDLE, GetKey());
	}

	if (Input()->IsPush(INPUT_KEY_JUMP))
	{
		ChangeState(STATE_KEY_JUMP, GetKey());
	}


	if (Input()->IsPush(INPUT_KEY_ATTACK))
	{
		ChangeState(STATE_KEY_ATTACK1, GetKey());
	}

	//�Ή������X�L���̃{�^����������Ă����炻�̃X�L���̃X�e�[�g�Ɉړ�
	ChangeSkillState();

}

void ActionGame::CMoveState::End()
{
}

void ActionGame::CMoveState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CMoveState::GetKey() const
{
	return STATE_KEY_MOVE;
}

void ActionGame::CMoveState::InputDash()
{
	if (Input()->IsNegativeDoublePush(INPUT_KEY_HORIZONTAL) || Input()->IsDoublePush(INPUT_KEY_HORIZONTAL) ||
		Input()->IsNegativeDoublePush(INPUT_KEY_VERTICAL) || Input()->IsDoublePush(INPUT_KEY_VERTICAL))
	{
		ChangeState(STATE_KEY_RUN, GetKey());
		return;
	}
}
