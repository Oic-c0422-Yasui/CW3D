#include "MutantMoveStateAI.h"
#include	"Player.h"
#include	"Collision.h"
#include	"InputDefine.h"
#include	"ParameterDefine.h"
#include	"ServiceLocator.h"



ActionGame::CMutantMoveStateAI::CMutantMoveStateAI(Vector3 vigilangeRange, Vector3 attackRange, Vector3 skillRange,
	int attackTiming, int skillTiming, float skillStartHpRate)
	: CBaseStateAI()
	, startSkillHPRate_(skillStartHpRate)
	, currentLostTime_(0)
	, attackRange_(attackRange)
	, vigilangeRange_(vigilangeRange)
	, skillRange_(skillRange)
	, attackTiming_(attackTiming)
	, skillTiming_(skillTiming)
{
}

void ActionGame::CMutantMoveStateAI::RegisterKey()
{
	Input()->AddKey(INPUT_KEY_HORIZONTAL);
	Input()->AddKey(INPUT_KEY_VERTICAL);
	Input()->AddKey(INPUT_KEY_ATTACK);
	Input()->AddKey(INPUT_KEY_SKILL1);
}

void ActionGame::CMutantMoveStateAI::Start()
{
	currentLostTime_ = 0;
}

void ActionGame::CMutantMoveStateAI::Update()
{
	//ターゲット取得
	const auto& target = CServiceLocator< CPlayer >::GetService();
	if (target->IsDead())
	{
		return;
	}

	//アクター取得
	const auto& transform = Actor()->GetTransform();

	//警戒範囲内にプレイヤーがいなくなるとカウントして一定後に停止
	if (!IsInRange(vigilangeRange_, target->GetCollider()))
	{

		currentLostTime_++;
		if (currentLostTime_ < 30)
		{
			//移動入力
			InputMove(-1.0f, target->GetPosition());
		}

	}
	else
	{
		currentLostTime_ = 0;
		//移動入力
		InputMove(-attackRange_.x, target->GetPosition());
	}

	//攻撃ボックス
	if (IsInRange(attackRange_, target->GetCollider()))
	{
		if (CUtilities::Random(attackTiming_) == 0)
		{
			Input()->SetKeyValue(INPUT_KEY_ATTACK, 1.0f);
		}
	}
	
	//攻撃ボックス
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

void ActionGame::CMutantMoveStateAI::End()
{
}

void ActionGame::CMutantMoveStateAI::ActivateSkill()
{
	const auto& hp = Actor()->GetParameterMap()->Get<CReactiveParameter<int>>(PARAMETER_KEY_HP);
	const auto& maxHp = Actor()->GetParameterMap()->Get<CReactiveParameter<int>>(PARAMETER_KEY_MAX_HP);
	float ratio = (float)hp / (float)maxHp;
	if (ratio <= startSkillHPRate_)
	{
		Input()->SetKeyValue(INPUT_KEY_SKILL1, 1.0f);
	}
}