#include "MoveStateAI.h"

ActionGame::CMoveStateAI::CMoveStateAI(Vector3 vigilangeRange, Vector3 attackRange, int timing)
	: CBaseStateAI()
	, currentLostTime_(0)
	, isAttack_(false)
	, attackRange_(attackRange)
	, vigilangeRange_(vigilangeRange)
	, attackTiming_(timing)
{
}

void ActionGame::CMoveStateAI::RegisterKey()
{
	Input()->AddKey(INPUT_KEY_HORIZONTAL);
	Input()->AddKey(INPUT_KEY_VERTICAL);
	Input()->AddKey(INPUT_KEY_ATTACK);
}

void ActionGame::CMoveStateAI::Start()
{
	currentLostTime_ = 0;
	isAttack_ = false;
}

void ActionGame::CMoveStateAI::Update()
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
		if (currentLostTime_ < 5)
		{
			Input()->SetKeyValue(INPUT_KEY_HORIZONTAL, transform->IsReverse() ? -1.0f : 1.0f);
		}
		//プレイヤーと5ｍ以上離れている場合
		else if (!IsInRange(5.0f, target->GetPosition()))
		{
			//移動入力
			InputMove(-5.0f, target->GetPosition());
		}
		return;
	}
	else
	{
		currentLostTime_ = 0;
	}
	

	//攻撃ボックス
	if (IsInRange(attackRange_, target->GetCollider()))
	{
		if (CUtilities::Random(attackTiming_) == 0)
		{
			Input()->SetKeyValue(INPUT_KEY_ATTACK, 1.0f);
			isAttack_ = true;
		}
	}
	else
	{
		//移動入力
		InputMove(-5.0f, target->GetPosition());
	}

}
