#include "MoveStateAI.h"

ActionGame::CMoveStateAI::CMoveStateAI(Vector3 vigilangeRange, Vector3 attackRange, int timing)
	: CStateAI()
	, currentLostTime(0)
	, isAttack(false)
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
	currentLostTime = 0;
	isAttack = false;
}

void ActionGame::CMoveStateAI::Update()
{
	//プレイヤー取得
	const auto& target = CServiceLocator< CPlayer >::GetService();
	const auto& transform = Actor()->GetTransform();
	//警戒ボックス
	CAABB collider;
	collider.SetPosition(transform->GetPosition());
	collider.Size = vigilangeRange_;
	
	//警戒範囲内にプレイヤーがいなくなるとカウントして一定後に停止
	if (!CCollision::Collision(target->GetCollider(), collider))
	{
		//距離計算
		Vector2 vec(transform->GetPosition().x - target->GetPosition().x, transform->GetPosition().z - target->GetPosition().z);
		float length = sqrt(vec.x * vec.x + vec.y * vec.y);

		currentLostTime++;
		if (currentLostTime < 5)
		{
			Input()->SetKeyValue(INPUT_KEY_HORIZONTAL, transform->IsReverse() ? -1.0f : 1.0f);
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
		return;
	}
	else
	{
		currentLostTime = 0;
	}
	//移動入力
	float sx = target->GetPosition().x - transform->GetPosition().x;
	float sz = target->GetPosition().z - transform->GetPosition().z;
	sx /= 5.0f;
	sz /= 5.0f;
	sx = ((sx < -1.0f) ? -1.0f : ((sx > 1.0f) ? 1.0f : sx));
	sz = -((sz < -1.0f) ? -1.0f : ((sz > 1.0f) ? 1.0f : sz));

	//攻撃ボックス
	collider.Size = attackRange_;
	if (CCollision::Collision(target->GetCollider(), collider))
	{
		if (CUtilities::Random(attackTiming_) == 0)
		{
			Input()->SetKeyValue(INPUT_KEY_ATTACK, 1.0f);
			isAttack = true;
		}
	}
	else
	{
		Input()->SetKeyValue(INPUT_KEY_HORIZONTAL, sx);
		Input()->SetKeyValue(INPUT_KEY_VERTICAL, sz);
	}

}
