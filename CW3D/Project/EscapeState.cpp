#include "EscapeState.h"
#include "ParameterDefine.h"

ActionGame::CEscapeState::CEscapeState(Parameter param)
	: CAttackBaseState()
	, parameter_(param)
	, isThrough_(false)
	, isEscapeCurrentTime_(0.0f)
	, isEscape_(false)
{
}

void ActionGame::CEscapeState::Start()
{
	action_ = Actor()->GetAction<CEscapeAction>(GetKey());
	CAttackBaseState::Start();
	isThrough_ = false;
	isEscape_ = false;
	isEscapeCurrentTime_ = 0.0f;
	action_->Start();

	auto& armorLevel = Actor()->GetParameterMap()->Get<BYTE>(PARAMETER_KEY_ARMORLEVEL);
	armorLevel = parameter_.armorLevel;

	if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) ||
		Input()->IsPress(INPUT_KEY_HORIZONTAL))
	{
		action_->Move(Input()->GetAxis(INPUT_KEY_HORIZONTAL), -(Input()->GetAxis(INPUT_KEY_VERTICAL)));
	}
	else
	{
		if (Actor()->IsReverse())
		{
			action_->Move(1, -(Input()->GetAxis(INPUT_KEY_VERTICAL)));
		}
		else
		{
			action_->Move(-1, -(Input()->GetAxis(INPUT_KEY_VERTICAL)));
		}
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

		if (isEscapeCurrentTime_ < parameter_.EscapeTime)
		{
			auto& isEscape_ = Actor()->GetParameterMap()->Get<bool>(PARAMETER_KEY_ESCAPE);
			if (!isEscape_)
			{
				isEscape_ = true;
			}
			isEscapeCurrentTime_ += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());
			if (isEscapeCurrentTime_ >= parameter_.EscapeTime)
			{
				isEscape_ = false;
			}

		}
	}

	

	CAttackBaseState::Execution();
}

void ActionGame::CEscapeState::InputExecution()
{
	float scale = TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());
	//タイムスケールが0以下の場合、入力を受け付けない
	if (scale <= 0.0f)
	{
		return;
	}
	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		if (Actor()->GetTransform()->GetPositionY() > 0)
		{
			ChangeState(STATE_KEY_FALL);
		}
		else
		{
			ChangeState(STATE_KEY_IDLE);
		}
	}
	if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) ||
		Input()->IsPress(INPUT_KEY_HORIZONTAL) ||
		Input()->IsNegativePress(INPUT_KEY_VERTICAL) ||
		Input()->IsPress(INPUT_KEY_VERTICAL))
	{
		if (currentTime_ > parameter_.ThroughEndTime)
		{
			if (Actor()->GetTransform()->GetPositionY() > 0)
			{
				if (GetKeepKey() == STATE_KEY_RUN)
				{
					ChangeState(STATE_KEY_RUN_FALL);
				}
				else
				{
					ChangeState(STATE_KEY_FALL);
				}
			}
			else
			{
				if (GetKeepKey() == STATE_KEY_RUN)
				{
					ChangeState(STATE_KEY_RUN);
				}
				else
				{
					ChangeState(STATE_KEY_MOVE);
				}
			}
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
