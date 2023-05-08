#include "JumpAttack1State.h"

ActionGame::CJumpAttack1State::CJumpAttack1State(Parameter param)
	: CAttackBaseState()
	, parameter_(param)
	, isStartCollide_(false)
{
}

void ActionGame::CJumpAttack1State::Start()
{
	action_ = Actor()->GetAction<CJumpAttack1Action>(GetKey());
	CAttackBaseState::Start();
	action_->Start();
	isStartCollide_ = false;
	const auto& gravity = parameter_.Gravity;
	Actor()->GetVelocity()->SetGravityScale(gravity.startScale, gravity.endScale, gravity.time);
	//当たり判定用の弾作成
	CreateShotAABB();

}

void ActionGame::CJumpAttack1State::Execution()
{

	for (auto& shot : shots_)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
		if (currentTime_ >= parameter_.CollideStartTime && !isStartCollide_)
		{
			shot->SetEnableCollider(true);
		}
		else if (currentTime_ >= parameter_.CollideEndTime)
		{
			shot->SetEnableCollider(false);
		}
	}

	if (currentTime_ >= parameter_.CollideStartTime && !isStartCollide_)
	{
		CreateEffect();
		isStartCollide_ = true;
	}


	if (currentTime_ > parameter_.EndTime)
	{
		ChangeState(STATE_KEY_FALL);
	}
	else if (isNextInput_)
	{
		if (currentTime_ > parameter_.NextInputTime)
		{
			ChangeState(STATE_KEY_RUN_JUMP_ATTACK2);
		}
	}
	CAttackBaseState::Execution();
}

void ActionGame::CJumpAttack1State::InputExecution()
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

void ActionGame::CJumpAttack1State::End()
{
	CAttackBaseState::End();
}

void ActionGame::CJumpAttack1State::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CJumpAttack1State::GetKey() const
{
	return STATE_KEY_JUMP_ATTACK1;
}
