#include "DamageState.h"
#include "ParameterDefine.h"

ActionGame::CDamageState::CDamageState()
	: CBaseState()
{
}

void ActionGame::CDamageState::Start()
{

	action_ = Actor()->GetAction<CDamageAction>(GetKey());
	action_->Start();

}

void ActionGame::CDamageState::Execution()
{
	action_->Execution();

	if (IsFly())
	{
		ChangeState(STATE_KEY_FLY_DAMAGE);
		//Õ“Ë”»’è‰ñ”ðON
		auto& isThroughCollision = Actor()->GetParameterMap()->Get<bool>(PARAMETER_KEY_THROUGH_COLLISION);
		isThroughCollision = true;
	}
	else
	{
		//Õ“Ë”»’è‰ñ”ðON
		auto& isThroughCollision = Actor()->GetParameterMap()->Get<bool>(PARAMETER_KEY_THROUGH_COLLISION);
		isThroughCollision = false;
	}

	if (Actor()->GetAnimationState()->IsEndMotion() && !IsFly())
	{
		ChangeState(STATE_KEY_IDLE);
	}
	auto& hp = Actor()->GetParameterMap()->Get<ActionGame::CReactiveParameter<int>>(PARAMETER_KEY_HP);
	if (hp <= 0)
	{
		auto state = IsFly() ? STATE_KEY_FLY_DAMAGE : STATE_KEY_DEAD;
		ChangeState(state);
	}
}

void ActionGame::CDamageState::InputExecution()
{
}

void ActionGame::CDamageState::End()
{
	action_->End();
	//Õ“Ë”»’è‰ñ”ðON
	auto& isThroughCollision = Actor()->GetParameterMap()->Get<bool>(PARAMETER_KEY_THROUGH_COLLISION);
	isThroughCollision = false;
}

void ActionGame::CDamageState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CDamageState::GetKey() const
{
	return STATE_KEY_DAMAGE;
}
