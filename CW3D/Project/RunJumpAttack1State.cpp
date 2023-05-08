#include "RunJumpAttack1State.h"

ActionGame::CRunJumpAttack1State::CRunJumpAttack1State(Parameter param)
	: CAttackBaseState()
	, parameter_(param)
	, isStartCollide_(false)
{
}

void ActionGame::CRunJumpAttack1State::Start()
{
	action_ = Actor()->GetAction<CRunJumpAttack1Action>(GetKey());
	CAttackBaseState::Start();
	action_->Start();
	const auto& gravity = parameter_.Gravity;
	Actor()->GetVelocity()->SetGravityScale(gravity.startScale, gravity.endScale, gravity.time);
	//当たり判定用の弾作成
	CreateShotAABB();

}

void ActionGame::CRunJumpAttack1State::Execution()
{

	for (auto& shot : shots_)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
		if (currentTime_ >= parameter_.CollideStartTime && !isStartCollide_)
		{
			shot->SetEnableCollider(true);
		}
	}
	if (currentTime_ >= parameter_.CollideStartTime && !isStartCollide_)
	{
		CreateEffect();
		isStartCollide_ = true;
	}


	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		ChangeState(STATE_KEY_FALL);
	}
	else if (isNextInput_)
	{
		if (Actor()->GetAnimationState()->GetTime() > parameter_.NextInputTime)
		{
			ChangeState(STATE_KEY_RUN_JUMP_ATTACK2);
		}
	}
	CAttackBaseState::Execution();
}

void ActionGame::CRunJumpAttack1State::InputExecution()
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

void ActionGame::CRunJumpAttack1State::End()
{
	CAttackBaseState::End();
	action_->End();
}

void ActionGame::CRunJumpAttack1State::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CRunJumpAttack1State::GetKey() const
{
	return STATE_KEY_RUN_JUMP_ATTACK1;
}
