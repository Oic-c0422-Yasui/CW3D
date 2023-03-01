#include "FlyDamageState.h"
#include "ParameterDefine.h"

ActionGame::CFlyDamageState::CFlyDamageState()
	: CState()
{
}

void ActionGame::CFlyDamageState::Start()
{
	action_ = Actor()->GetAction<CFlyDamageAction>(GetKey());
	action_->Start();
}

void ActionGame::CFlyDamageState::Execution()
{
	action_->Execution();

	if (Actor()->GetTransform()->GetPositionY() <= 0)
	{
		auto& hp = Actor()->GetParameterMap()->Get<ActionGame::CReactiveParameter<int>>(PARAMETER_KEY_HP);
		if (hp <= 0)
		{
			ChangeState(STATE_KEY_DEAD);
		}
		else
		{
			ChangeState(STATE_KEY_DOWN);
		}

	}
}

void ActionGame::CFlyDamageState::InputExecution()
{
}

void ActionGame::CFlyDamageState::End()
{
	action_->End();
}

void ActionGame::CFlyDamageState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CFlyDamageState::GetKey() const
{
	return STATE_KEY_FLY_DAMAGE;
}
