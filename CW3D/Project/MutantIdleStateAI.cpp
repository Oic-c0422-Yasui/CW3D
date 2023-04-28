#include "MutantIdleStateAI.h"
#include "ParameterDefine.h"

ActionGame::CMutantIdleStateAI::CMutantIdleStateAI(Vector3 vigilanceRange, Vector3 attackRange, int attackTiming)
	: CIdleStateAI(vigilanceRange, attackRange, attackTiming)
	, isAngry(false)
{
}

void ActionGame::CMutantIdleStateAI::RegisterKey()
{
	CIdleStateAI::RegisterKey();

}

void ActionGame::CMutantIdleStateAI::Start()
{
	CIdleStateAI::Start();
	const auto& hp = Actor()->GetParameterMap()->Get<CReactiveParameter<int>>(PARAMETER_KEY_HP);
	const auto& maxHp = Actor()->GetParameterMap()->Get<CReactiveParameter<int>>(PARAMETER_KEY_MAX_HP);
	float ratio = (float)hp / (float)maxHp;
	if (ratio > 0.4f)
	{
		isAngry = false;
	}
}

void ActionGame::CMutantIdleStateAI::Update()
{
	CIdleStateAI::Update();
	const auto& hp = Actor()->GetParameterMap()->Get<CReactiveParameter<int>>(PARAMETER_KEY_HP);
	const auto& maxHp = Actor()->GetParameterMap()->Get<CReactiveParameter<int>>(PARAMETER_KEY_MAX_HP);
	float ratio = (float)hp / (float)maxHp;
	if (ratio <= 0.4f)
	{
		if (!isAngry)
		{
			StateMachine()->ChangeState(STATE_KEY_SPEAR_ATTACK);
			isAngry = true;
		}
	}
}

void ActionGame::CMutantIdleStateAI::End()
{
	CIdleStateAI::End();
}
