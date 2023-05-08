#include "MutantIdleStateAI.h"
#include "ParameterDefine.h"
#include	"Player.h"
#include	"Collision.h"
#include	"Common.h"
#include	"InputDefine.h"
#include	"ServiceLocator.h"


ActionGame::CMutantIdleStateAI::CMutantIdleStateAI(Vector3 vigilanceRange, Vector3 attackRange, Vector3 skillRange,
					int attackTiming, int skillTiming, float skillStartHpRate)
	: CBaseStateAI()
	, vigilanceRange_(vigilanceRange)
	, attackRange_(attackRange)
	, skillRange_(skillRange)
	, attackTiming_(attackTiming)
	, skillTiming_(skillTiming)
	, startSkillHPRate_(skillStartHpRate)
{
}

void ActionGame::CMutantIdleStateAI::RegisterKey()
{
	Input()->AddKey(INPUT_KEY_HORIZONTAL);
	Input()->AddKey(INPUT_KEY_VERTICAL);
	Input()->AddKey(INPUT_KEY_ATTACK);
	Input()->AddKey(INPUT_KEY_SKILL1);
}

void ActionGame::CMutantIdleStateAI::Start()
{

}

void ActionGame::CMutantIdleStateAI::Update()
{

	//É^Å[ÉQÉbÉgéÊìæ
	const auto& target = CServiceLocator< CPlayer >::GetService();
	if (target->IsDead())
	{
		return;
	}

	//ÉAÉNÉ^Å[éÊìæ
	const auto& transform = Actor()->GetTransform();


	//åxâ˙îÕàÕì‡Ç…ì¸Ç¡ÇƒÇ´ÇΩÇÁà⁄ìÆ
	if (IsInRange(vigilanceRange_, target->GetCollider()))
	{
		
		//çUåÇîÕàÕì‡Ç…ì¸Ç¡ÇƒÇ´ÇΩÇÁçUåÇ
		if (IsInRange(attackRange_, target->GetCollider()))
		{
			if (CUtilities::Random(attackTiming_) == 0)
			{
				transform->SetReverse(target->GetPosition().x < transform->GetPosition().x ? true : false);
				Input()->SetKeyValue(INPUT_KEY_ATTACK, 1.0f);
			}
			
		}
		else
		{
			if (!Input()->IsPush(INPUT_KEY_HORIZONTAL) && !Input()->IsNegativePush(INPUT_KEY_HORIZONTAL))
			{
				Input()->SetKeyValue(INPUT_KEY_HORIZONTAL,
					target->GetPosition().x < transform->GetPosition().x ? -CUtilities::RandomFloat() : CUtilities::RandomFloat());
			}
			if (!Input()->IsPush(INPUT_KEY_VERTICAL) && !Input()->IsNegativePush(INPUT_KEY_VERTICAL) && CUtilities::Random(10) == 0)
			{
				Input()->SetKeyValue(INPUT_KEY_VERTICAL,
					CUtilities::Random(10) < 4 ? -CUtilities::RandomFloat() : CUtilities::RandomFloat());
			}
		}

		if (IsInRange(skillRange_, target->GetCollider()))
		{
			if (CUtilities::Random(skillTiming_) == 0)
			{
				transform->SetReverse(target->GetPosition().x < transform->GetPosition().x ? true : false);
				StateMachine()->ChangeState(STATE_KEY_SLASH_ATTACK);
			}
			else if (CUtilities::Random(attackTiming_) == 0)
			{
				ActivateSkill();
			}
		}
	}
	//í‚é~íÜÇ…ÉâÉìÉ_ÉÄÇ≈ìKìñÇ…ãtï˚å¸ì¸óÕ
	else if (CUtilities::Random(50) == 0)
	{

		Input()->SetKeyValue(INPUT_KEY_HORIZONTAL,
			transform->IsReverse() ? 1.0f : -1.0f);

	}

}

void ActionGame::CMutantIdleStateAI::End()
{
	
}

void ActionGame::CMutantIdleStateAI::ActivateSkill()
{
	const auto& hp = Actor()->GetParameterMap()->Get<CReactiveParameter<int>>(PARAMETER_KEY_HP);
	const auto& maxHp = Actor()->GetParameterMap()->Get<CReactiveParameter<int>>(PARAMETER_KEY_MAX_HP);
	float ratio = (float)hp / (float)maxHp;
	if (ratio <= startSkillHPRate_)
	{
		Input()->SetKeyValue(INPUT_KEY_SKILL1, 1.0f);
	}
}
