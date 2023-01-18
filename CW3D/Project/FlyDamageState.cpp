#include "FlyDamageState.h"
#include "ParameterDefine.h"

ActionGame::FlyDamageState::FlyDamageState()
	: State()
{
}

void ActionGame::FlyDamageState::Start()
{
	m_DamageAction = Actor()->GetAction<FlyDamageAction>(GetKey());
	m_DamageAction->Start();
}

void ActionGame::FlyDamageState::Execution()
{
	m_DamageAction->Execution();

	if (Actor()->GetTransform()->GetPositionY() <= 0)
	{
		auto& hp = Actor()->GetParameterMap()->Get<ActionGame::ReactiveParameter<int>>(PARAMETER_KEY_HP);
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

void ActionGame::FlyDamageState::InputExecution()
{
}

void ActionGame::FlyDamageState::End()
{
	m_DamageAction->End();
}

void ActionGame::FlyDamageState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::FlyDamageState::GetKey() const
{
	return STATE_KEY_FLY_DAMAGE;
}
