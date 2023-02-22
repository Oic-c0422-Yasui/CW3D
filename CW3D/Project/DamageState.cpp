#include "DamageState.h"
#include "ParameterDefine.h"

ActionGame::DamageState::DamageState(Parameter param)
	: State()
	, m_Parameter(param)
	, currentTime_(0.0f)
{
}

void ActionGame::DamageState::Start()
{
	currentTime_ = 0.0f;
	m_DamageAction = Actor()->GetAction<DamageAction>(GetKey());
	m_DamageAction->Start();

}

void ActionGame::DamageState::Execution()
{
	m_DamageAction->Execution();

	if (Actor()->GetTransform()->GetPositionY() > 0)
	{
		ChangeState(STATE_KEY_FLY_DAMAGE);
	}

	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		ChangeState(STATE_KEY_IDLE);
	}
	auto& hp = Actor()->GetParameterMap()->Get<ActionGame::ReactiveParameter<int>>(PARAMETER_KEY_HP);
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

void ActionGame::DamageState::InputExecution()
{
}

void ActionGame::DamageState::End()
{
	m_DamageAction->End();
}

void ActionGame::DamageState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::DamageState::GetKey() const
{
	return STATE_KEY_DAMAGE;
}
