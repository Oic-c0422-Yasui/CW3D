#include "Attack2State.h"

using namespace ActionGame;

ActionGame::CAttack2State::CAttack2State(Parameter param)
	: CAttackBaseState()
	, parameter_(param)
	, isStartCollide_(false)
{
}

void ActionGame::CAttack2State::Start()
{
	action_ = Actor()->GetAction<CAttack2Action>(GetKey());

	CAttackBaseState::Start();

	action_->Start();
	isStartCollide_ = false;
	//当たり判定用の弾作成
	CreateShotAABB();

}

void ActionGame::CAttack2State::Execution()
{

	for (auto& shot : shots_)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
		if (currentTime_ >= parameter_.CollideStartFrameTime && !isStartCollide_)
		{
			shot->SetEnableCollider(true);


		}
		else if (shot->IsEnableCollider())
		{
			shot->SetEnableCollider(false);
		}
	}
	if (currentTime_ >= parameter_.CollideStartFrameTime && !isStartCollide_)
	{
		isStartCollide_ = true;
	}

	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		ChangeState(STATE_KEY_IDLE);
	}
	else if (isNextInput_)
	{
		if (currentTime_ > parameter_.NextInputFrameTime)
		{
			ChangeState(STATE_KEY_ATTACK3);
		}
	}
	CAttackBaseState::Execution();
}

void ActionGame::CAttack2State::InputExecution()
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

void ActionGame::CAttack2State::End()
{
	CAttackBaseState::End();
}

void ActionGame::CAttack2State::CollisionEvent(unsigned int type, std::any obj)
{
}

const StateKeyType ActionGame::CAttack2State::GetKey() const
{
	return STATE_KEY_ATTACK2;
}
