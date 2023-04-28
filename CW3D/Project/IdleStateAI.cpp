#include "IdleStateAI.h"

ActionGame::CIdleStateAI::CIdleStateAI(Vector3 vigilanceRange, Vector3 attackRange, int attackTiming)
	: CBaseStateAI()
	, isAttack_(false)
	, vigilangeRange_(vigilanceRange)
	, attackRange_(attackRange)
	, attackTiming_(attackTiming)
{
}

void ActionGame::CIdleStateAI::RegisterKey()
{
	Input()->AddKey(INPUT_KEY_HORIZONTAL);
	Input()->AddKey(INPUT_KEY_VERTICAL);
	Input()->AddKey(INPUT_KEY_ATTACK);
}

void ActionGame::CIdleStateAI::Start()
{
	isAttack_ = false;
}

void ActionGame::CIdleStateAI::Update()
{
	//ターゲット取得
	const auto& target = CServiceLocator< CPlayer >::GetService();
	if (target->IsDead())
	{
		return;
	}

	//アクター取得
	const auto& transform = Actor()->GetTransform();


	//警戒範囲内に入ってきたら移動
	if (IsInRange(vigilangeRange_, target->GetCollider()))
	{

		//攻撃範囲内に入ってきたら攻撃
		if (IsInRange(attackRange_, target->GetCollider()))
		{
			if (!Input()->IsPush(INPUT_KEY_ATTACK) && CUtilities::Random(attackTiming_) == 0)
			{
				transform->SetReverse(target->GetPosition().x < transform->GetPosition().x ? true : false);
				Input()->SetKeyValue(INPUT_KEY_ATTACK, 1.0f);
				isAttack_ = true;
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
	}
	//停止中にランダムで適当に逆方向入力
	else if (CUtilities::Random(50) == 0)
	{

		Input()->SetKeyValue(INPUT_KEY_HORIZONTAL,
			transform->IsReverse() ? 1.0f : -1.0f);

	}
	//停止中にランダムで適当にプレイヤー方向入力
	else if (CUtilities::Random(50) == 0)
	{
		Input()->SetKeyValue(INPUT_KEY_HORIZONTAL,
			target->GetPosition().x < transform->GetPosition().x ? -1.0f : 1.0f);
	}
	//プレイヤーと5ｍ以上離れている場合
	else if (!IsInRange(5.0f,target->GetPosition()))
	{
		//移動入力
		InputMove(5.0f, target->GetPosition());
	}

}

void ActionGame::CIdleStateAI::End()
{
}
