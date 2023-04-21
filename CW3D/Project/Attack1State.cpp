#include "Attack1State.h"

using namespace ActionGame;

ActionGame::CAttack1State::CAttack1State(Parameter param)
	: CAttackBaseState()
	, parameter_(param)
	, isStartCollide_(false)
{
}

void ActionGame::CAttack1State::Start()
{
	action_ = Actor()->GetAction<CAttack1Action>(GetKey());
	isStartCollide_ = false;

	SettingMoveCompensationParam(parameter_.MoveCompensationParam);
	CAttackBaseState::Start();

	action_->Start();

	//当たり判定用の弾作成
	CreateShotAABB();

}

void ActionGame::CAttack1State::Execution() 
{
	moveCompentionParam_.currentTime = currentTime_;

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

void ActionGame::CAttack1State::InputExecution()
{
	float scale = TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());
	//タイムスケールが0以下の場合、入力を受け付けない
	if (scale <= 0.0f)
	{
		return;
	}
	if (Input()->IsPush(INPUT_KEY_ATTACK))
	{
		isNextInput_ = true;
	}

	CAttackBaseState::InputExecution();
}

void ActionGame::CAttack1State::End()
{
	CAttackBaseState::End();
}

void ActionGame::CAttack1State::CollisionEvent(unsigned int type, std::any obj)
{
}

const StateKeyType ActionGame::CAttack1State::GetKey() const
{
	return STATE_KEY_ATTACK1;
}
