#include "AttackStateAI.h"

ActionGame::CAttackStateAI::CAttackStateAI()
	: CStateAI()
	, currentLostTime(0)
{
}

void ActionGame::CAttackStateAI::RegisterKey()
{
	Input()->AddKey(INPUT_KEY_HORIZONTAL);
	Input()->AddKey(INPUT_KEY_VERTICAL);
	Input()->AddKey(INPUT_KEY_ATTACK);
}

void ActionGame::CAttackStateAI::Start()
{
	currentLostTime = 0;
}

void ActionGame::CAttackStateAI::Update()
{
	//ターゲット取得
	const auto& target = CServiceLocator< CPlayer >::GetService();
	//アクター取得
	const auto& transform = Actor()->GetTransform();
	//警戒ボックス
	CAABB collider;
	collider.SetPosition(transform->GetPosition());
	collider.Size = Vector3(1.2f, 1, 1.0f);

	//警戒範囲内に入ってきたら攻撃
	if (CCollision::Collision(target->GetCollider(), collider))
	{
		Input()->SetKeyValue(INPUT_KEY_ATTACK, 1.0f);
	}
}

void ActionGame::CAttackStateAI::End()
{
}
