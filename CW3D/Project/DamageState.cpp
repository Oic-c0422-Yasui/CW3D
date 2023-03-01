#include "DamageState.h"
#include "ParameterDefine.h"

ActionGame::CDamageState::CDamageState(Parameter param)
	: CState()
	, parameter_(param)
	, currentTime_(0.0f)
{
}

void ActionGame::CDamageState::Start()
{
	currentTime_ = 0.0f;
	action_ = Actor()->GetAction<CDamageAction>(GetKey());
	action_->Start();

}

void ActionGame::CDamageState::Execution()
{
	action_->Execution();

	if (Actor()->GetTransform()->GetPositionY() > 0)
	{
		ChangeState(STATE_KEY_FLY_DAMAGE);
	}

	if (Actor()->GetAnimationState()->IsEndMotion() && Actor()->GetTransform()->GetPositionY() <= 0)
	{
		ChangeState(STATE_KEY_IDLE);
	}
	auto& hp = Actor()->GetParameterMap()->Get<ActionGame::CReactiveParameter<int>>(PARAMETER_KEY_HP);
	if (hp <= 0)
	{
		if (Actor()->GetTransform()->GetPositionY() > 0)
		{
			ChangeState(STATE_KEY_FLY_DAMAGE);
		}
		else
		{
			ChangeState(STATE_KEY_DEAD);
		}
	}
}

void ActionGame::CDamageState::InputExecution()
{
}

void ActionGame::CDamageState::End()
{
	action_->End();
}

void ActionGame::CDamageState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CDamageState::GetKey() const
{
	return STATE_KEY_DAMAGE;
}
