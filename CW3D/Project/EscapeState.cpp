#include "EscapeState.h"
#include "ParameterDefine.h"

ActionGame::CEscapeState::CEscapeState(Parameter param)
	: CAttackBaseState()
	, parameter_(param)
	, isThrough_(false)
	, currenteEcapeTime_(0.0f)
	, isEscape_(false)
{
}

void ActionGame::CEscapeState::Start()
{
	action_ = Actor()->GetAction<CEscapeAction>(GetKey());
	CAttackBaseState::Start();
	isThrough_ = false;
	isEscape_ = false;
	currenteEcapeTime_ = 0.0f;
	action_->Start();

	SetArmorLevel(parameter_.armorLevel);

	if (IsPressHorizontalKey())
	{
		action_->Move(Input()->GetAxis(INPUT_KEY_HORIZONTAL), 
					-(Input()->GetAxis(INPUT_KEY_VERTICAL)));
	}
	else
	{
		auto dirX = Actor()->IsReverse() ? 1.0f : -1.0f;

		action_->Move(dirX, -(Input()->GetAxis(INPUT_KEY_VERTICAL)));
	}
}

void ActionGame::CEscapeState::Execution()
{

	if (currentTime_ > parameter_.ThroughStartTime && !isThrough_)
	{
		action_->StartThrough();
		isThrough_ = true;
	}

	//ジャスト回避時間
	if (currentTime_ >= parameter_.EscapeStartTime)
	{

		if (currenteEcapeTime_ < parameter_.EscapeTime)
		{
			auto& isEscape_ = Actor()->GetParameterMap()->Get<bool>(PARAMETER_KEY_ESCAPE);
			if (!isEscape_)
			{
				isEscape_ = true;
			}
			currenteEcapeTime_ += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());
			if (currenteEcapeTime_ >= parameter_.EscapeTime)
			{
				isEscape_ = false;
			}

		}
	}

	

	CAttackBaseState::Execution();
}

void ActionGame::CEscapeState::InputExecution()
{
	//タイムスケールが0以下の場合、入力を受け付けない
	if (IsTimeScaleZero())
	{
		return;
	}

	//アニメーション終了時、待機状態へ移行
	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		SwitchFlyChangeState(STATE_KEY_IDLE, STATE_KEY_FALL);
	}

	//回避終了時間が過ぎていれば移動可能
	if (currentTime_ > parameter_.ThroughEndTime)
	{
		if (IsPressMoveKey())
		{
			if (IsFly())
			{
				auto state = GetKeepKey() == STATE_KEY_RUN ?
					STATE_KEY_RUN_FALL : STATE_KEY_FALL;
				ChangeState(state);
			}
			else
			{
				auto state = GetKeepKey() == STATE_KEY_RUN ?
					STATE_KEY_RUN : STATE_KEY_MOVE;
				ChangeState(state);
			}
		}
	}
	//攻撃開始可能時間が過ぎていれば攻撃可能
	if (currentTime_ > parameter_.InputAttackStartTime)
	{
		if (Input()->IsPush(INPUT_KEY_ATTACK))
		{
			SwitchFlyChangeState(STATE_KEY_ATTACK1, STATE_KEY_JUMP_ATTACK1);
		}
	}
		

	CAttackBaseState::InputExecution();
}

void ActionGame::CEscapeState::End()
{
	CAttackBaseState::End();
	action_->End();
	auto& isEscape_ = Actor()->GetParameterMap()->Get<bool>(PARAMETER_KEY_ESCAPE);
	isEscape_ = false;
}

void ActionGame::CEscapeState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CEscapeState::GetKey() const
{
	return STATE_KEY_ESCAPE;
}
