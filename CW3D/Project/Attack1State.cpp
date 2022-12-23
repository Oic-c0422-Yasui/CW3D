#include "Attack1State.h"

using namespace ActionGame;

ActionGame::Attack1State::Attack1State(Parameter param)
	: AttackBaseState()
	, m_Parameter(param)
	, collideStartFlg(false)
{
}

void ActionGame::Attack1State::Start()
{
	m_Attack1Action = Actor()->GetAction<Attack1Action>(GetKey());
	collideStartFlg = false;
	AttackBaseState::Start();

	m_Attack1Action->Start();

	//“–‚½‚è”»’è—p‚Ì’eì¬
	CreateShotAABB();

}

void ActionGame::Attack1State::Execution() 
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
		CreateEffect();
		collideStartFlg = true;
	}
	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		ChangeState(STATE_KEY_IDLE);
	}
	else if (m_NextInputFlg)
	{
		if (Actor()->GetAnimationState()->GetTime() > m_Parameter.NextInputFrameTime)
		{
			ChangeState(STATE_KEY_ATTACK2);
		}
	}
	AttackBaseState::Execution();
}

void ActionGame::Attack1State::InputExecution()
{
	if (Input()->IsPush(INPUT_KEY_ATTACK))
	{
		m_NextInputFlg = true;
	}

	AttackBaseState::InputExecution();
}

void ActionGame::Attack1State::End()
{
	AttackBaseState::End();
}

void ActionGame::Attack1State::CollisionEvent(unsigned int type, std::any obj)
{
}

const StateKeyType ActionGame::Attack1State::GetKey() const
{
	return STATE_KEY_ATTACK1;
}
