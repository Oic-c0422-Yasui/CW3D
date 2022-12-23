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
	//“–‚½‚è”»’è—p‚Ì’eì¬
	CreateShotAABB();

}

void ActionGame::RunAttack1State::Execution()
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
	/*else if (m_NextInputFlg)
	{
		if (Actor()->GetAnimationState()->GetTime() > 0.7f)
		{
			ChangeState(STATE_KEY_ATTACK2);
		}
	}*/

	AttackBaseState::Execution();
}

void ActionGame::RunAttack1State::InputExecution()
{

	if (m_CurrentTime > m_Parameter.NextInputFrameTime)
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
	return STATE_KEY_RUNATTACK1;
}

