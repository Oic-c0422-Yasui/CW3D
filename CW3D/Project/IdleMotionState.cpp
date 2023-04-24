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
	//タイムスケールが0以下の場合、入力を受け付けない
	if (IsTimeScaleZero())
	{
		return;
	}

	//キーボードでの移動
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

	
	//対応したスキルのボタンが押されていたらそのスキルのステートに移動
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
