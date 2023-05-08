#include "DamageState.h"
#include "ParameterDefine.h"



ActionGame::CDamageState::CDamageState(Parameter param)
	: CBaseState()
	, parameter_(param)
{
}

void ActionGame::CDamageState::Start()
{
	auto& armor = Actor()->GetParameterMap()->Get<BYTE>(PARAMETER_KEY_ARMORLEVEL);
	armor = parameter_.armor;
	action_ = Actor()->GetAction<CDamageAction>(GetKey());
	action_->Start();

}

void ActionGame::CDamageState::Execution()
{
	action_->Execution();

	if (IsFly())
	{
		ChangeState(STATE_KEY_FLY_DAMAGE);
		//ΥΛ»θρπON
		auto& isThroughCollision = Actor()->GetParameterMap()->Get<bool>(PARAMETER_KEY_THROUGH_COLLISION);
		isThroughCollision = true;
	}
	else
	{
		//ΥΛ»θρπOFF
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

	//ΥΛ»θρπOFF
	auto& param = Actor()->GetParameterMap();
	auto& isThroughCollision = param->Get<bool>(PARAMETER_KEY_THROUGH_COLLISION);
	isThroughCollision = false;
	//A[}[xπ³Ιί·
	auto& armor = param->Get<BYTE>(PARAMETER_KEY_ARMORLEVEL);
	const auto& defaultArmor = param->Get<BYTE>(PARAMETER_KEY_DEFAULT_ARMORLEVEL);
	armor = defaultArmor;
}

void ActionGame::CDamageState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CDamageState::GetKey() const
{
	return STATE_KEY_DAMAGE;
}
