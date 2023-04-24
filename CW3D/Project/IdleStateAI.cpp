#include "IdleStateAI.h"

ActionGame::CIdleStateAI::CIdleStateAI(Vector3 vigilanceRange, Vector3 attackRange, int attackTiming)
	: CStateAI()
	, isAttack(false)
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
	isAttack = false;
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
	//警戒ボックス
	CAABB collider;
	collider.SetPosition(transform->GetPosition());
	collider.Size = vigilangeRange_;

	//距離計算
	const Vector2 vec(transform->GetPosition().x - target->GetPosition().x, transform->GetPosition().z - target->GetPosition().z);
	const float length = sqrt(vec.x * vec.x + vec.y * vec.y);

	//警戒範囲内に入ってきたら移動
	if (CCollision::Collision(target->GetCollider(), collider))
	{
		collider.Size = attackRange_;
		//攻撃範囲内に入ってきたら攻撃
		if (CCollision::Collision(target->GetCollider(), collider))
		{
			if (!Input()->IsPush(INPUT_KEY_ATTACK) && CUtilities::Random(attackTiming_) == 0)
			{
				transform->SetReverse(target->GetPosition().x < transform->GetPosition().x ? true : false);
				Input()->SetKeyValue(INPUT_KEY_ATTACK, 1.0f);
				isAttack = true;
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
	else if (length > 5.0f)
	{
		//移動入力
		float sx = target->GetPosition().x - transform->GetPosition().x;
		float sz = target->GetPosition().z - transform->GetPosition().z;
		sx /= 5.0f;
		sz /= 5.0f;
		sx = ((sx < -1.0f) ? -1.0f : ((sx > 1.0f) ? 1.0f : sx));
		sz = -((sz < -1.0f) ? -1.0f : ((sz > 1.0f) ? 1.0f : sz));
		Input()->SetKeyValue(INPUT_KEY_HORIZONTAL, sx);
		Input()->SetKeyValue(INPUT_KEY_VERTICAL, sz);
	}

}

void ActionGame::CIdleStateAI::End()
{
}
