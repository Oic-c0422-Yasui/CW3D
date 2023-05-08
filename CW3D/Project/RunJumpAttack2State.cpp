#include "RunJumpAttack2State.h"

ActionGame::CRunJumpAttack2State::CRunJumpAttack2State(Parameter param)
	: CAttackBaseState()
	, parameter_(param)
{
}

void ActionGame::CRunJumpAttack2State::Start()
{
	action_ = Actor()->GetAction<CRunJumpAttack2Action>(GetKey());
	CAttackBaseState::Start();
	action_->Start();
	const auto& gravity = parameter_.Gravity;
	Actor()->GetVelocity()->SetGravityScale(gravity.startScale, gravity.endScale, gravity.time);
	//当たり判定用の弾作成
	CreateShotAABB();
}

void ActionGame::CRunJumpAttack2State::Execution()
{

	for (auto& shot : shots_)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
	}

	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		ChangeState(STATE_KEY_FALL);
	}
	if (isNextInput_)
	{
		if (currentTime_ > parameter_.NextInputTime)
		{
			ChangeState(STATE_KEY_RUN_JUMP_ATTACK3);
		}
	}
	CAttackBaseState::Execution();
}

void ActionGame::CRunJumpAttack2State::InputExecution()
{
	//タイムスケールが0以下の場合、入力を受け付けない
	if (IsTimeScaleZero())
	{
		return;
	}
	if (Input()->IsPush(INPUT_KEY_ATTACK))
	{
		isNextInput_ = true;
	}

	CAttackBaseState::InputExecution();
}

void ActionGame::CRunJumpAttack2State::End()
{
	CAttackBaseState::End();
	action_->End();
}

void ActionGame::CRunJumpAttack2State::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CRunJumpAttack2State::GetKey() const
{
	return STATE_KEY_RUN_JUMP_ATTACK2;
}
