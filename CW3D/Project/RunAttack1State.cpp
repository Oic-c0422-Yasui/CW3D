#include "RunAttack1State.h"

ActionGame::RunAttack1State::RunAttack1State(Parameter param)
	: AttackBaseState()
	, m_Parameter(param)
	, collideStartFlg(false)
{
}

void ActionGame::RunAttack1State::Start()
{
	m_RunAttack1Action = Actor()->GetAction<RunAttack1Action>(GetKey());

	collideStartFlg = false;
	AttackBaseState::Start();

	m_RunAttack1Action->Start();
	//当たり判定用の弾作成
	CreateShotAABB();

}

void ActionGame::RunAttack1State::Execution()
{

	for (auto& shot : m_pShots)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
		if (currentTime_ >= m_Parameter.CollideStartFrameTime && !collideStartFlg)
		{
			shot->SetEnableCollider(true);
		}
		else if (shot->IsEnableCollider())
		{
			shot->SetEnableCollider(false);
		}
	}

	if (currentTime_ >= m_Parameter.CollideStartFrameTime && !collideStartFlg)
	{
		CreateEffect();
		collideStartFlg = true;
	}


	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		ChangeState(STATE_KEY_IDLE);
	}

	AttackBaseState::Execution();
}

void ActionGame::RunAttack1State::InputExecution()
{
	float scale = TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());
	//タイムスケールが0以下の場合、入力を受け付けない
	if (scale <= 0.0f)
	{
		return;
	}
	if (currentTime_ > m_Parameter.NextInputFrameTime)
	{
		if (Input()->IsPush(INPUT_KEY_ATTACK))
		{
			ChangeState(STATE_KEY_ATTACK1);
		}
	}

	AttackBaseState::InputExecution();

}

void ActionGame::RunAttack1State::End()
{
	AttackBaseState::End();
}

void ActionGame::RunAttack1State::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::RunAttack1State::GetKey() const
{
	return STATE_KEY_RUN_ATTACK1;
}

