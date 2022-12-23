#include "Attack2State.h"

using namespace ActionGame;

ActionGame::Attack2State::Attack2State(Parameter param)
	: AttackBaseState()
	, m_Parameter(param)
	, collideStartFlg(false)
{
}

void ActionGame::Attack2State::Start()
{
	m_Attack2Action = Actor()->GetAction<Attack2Action>(GetKey());

	AttackBaseState::Start();

	m_Attack2Action->Start();
	collideStartFlg = false;
	//“–‚½‚è”»’è—p‚Ì’eì¬
	CreateShotAABB();

}

void ActionGame::Attack2State::Execution()
{

	for (auto& shot : m_pShots)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
		if (m_CurrentTime >= m_Parameter.CollideStartFrameTime && !collideStartFlg)
		{
			shot->SetEnableCollider(true);


		}
		else if (shot->IsEnableCollider())
		{
			shot->SetEnableCollider(false);
		}
	}
	if (m_CurrentTime >= m_Parameter.CollideStartFrameTime && !collideStartFlg)
	{
		collideStartFlg = true;
	}

	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		ChangeState(STATE_KEY_IDLE);
	}
	else if (m_NextInputFlg)
	{
		if (m_CurrentTime > m_Parameter.NextInputFrameTime)
		{
			ChangeState(STATE_KEY_ATTACK3);
		}
	}
	AttackBaseState::Execution();
}

void ActionGame::Attack2State::InputExecution()
{

	if (Input()->IsPush(INPUT_KEY_ATTACK))
	{
		m_NextInputFlg = true;
	}

	AttackBaseState::InputExecution();

}

void ActionGame::Attack2State::End()
{
	AttackBaseState::End();
}

void ActionGame::Attack2State::CollisionEvent(unsigned int type, std::any obj)
{
}

const StateKeyType ActionGame::Attack2State::GetKey() const
{
	return STATE_KEY_ATTACK2;
}
