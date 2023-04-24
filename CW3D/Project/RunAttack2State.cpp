#include "RunAttack2State.h"

ActionGame::CRunAttack2State::CRunAttack2State(Parameter param)
	: CAttackBaseState()
	, parameter_(param)
	, isStartCollide_(false)
{
}

void ActionGame::CRunAttack2State::Start()
{
	action_ = Actor()->GetAction<CAttack1Action>(GetKey());
	isStartCollide_ = false;

	CAttackBaseState::Start();

	action_->Start();

	//当たり判定用の弾作成
	CreateShotAABB();
}

void ActionGame::CRunAttack2State::Execution()
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
		CreateEffect();
		isStartCollide_ = true;
	}
	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		ChangeState(STATE_KEY_IDLE);
	}
	else if (isNextInput_)
	{
		if (Actor()->GetAnimationState()->GetTime() > parameter_.NextInputFrameTime)
		{
			ChangeState(STATE_KEY_ATTACK2);
		}
	}
	CAttackBaseState::Execution();
}

void ActionGame::CRunAttack2State::InputExecution()
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

void ActionGame::CRunAttack2State::End()
{
	CAttackBaseState::End();
}

void ActionGame::CRunAttack2State::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CRunAttack2State::GetKey() const
{
	return STATE_KEY_RUN_ATTACK2;
}
