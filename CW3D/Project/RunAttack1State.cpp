#include "RunAttack1State.h"
#include "AnimationUtilities.h"


ActionGame::CRunAttack1State::CRunAttack1State(Parameter param)
	: CAttackBaseState()
	, parameter_(param)
	, isStartCollide_(false)
{
}

void ActionGame::CRunAttack1State::Start()
{
	action_ = Actor()->GetAction<CRunAttack1Action>(GetKey());

	isStartCollide_ = false;

	CAttackBaseState::Start();

	action_->Start();
	//当たり判定用の弾作成
	CreateShotAABB();

}

void ActionGame::CRunAttack1State::Execution()
{

	const auto pos = Actor()->GetPosition();
	for (auto& shot : shots_)
	{
		shot->SetPosition(pos + shot->GetOffset());
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
		CreateEffect();
		isStartCollide_ = true;
	}


	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		ChangeState(STATE_KEY_IDLE);
	}

	CAttackBaseState::Execution();
}

void ActionGame::CRunAttack1State::InputExecution()
{
	//タイムスケールが0以下の場合、入力を受け付けない
	if (IsTimeScaleZero())
	{
		return;
	}
	if (currentTime_ > parameter_.NextInputFrameTime)
	{
		if (Input()->IsPush(INPUT_KEY_ATTACK))
		{
			ChangeState(STATE_KEY_RUN_ATTACK2);
		}
	}

	CAttackBaseState::InputExecution();

}

void ActionGame::CRunAttack1State::End()
{
	CAttackBaseState::End();
}

void ActionGame::CRunAttack1State::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CRunAttack1State::GetKey() const
{
	return STATE_KEY_RUN_ATTACK1;
}

