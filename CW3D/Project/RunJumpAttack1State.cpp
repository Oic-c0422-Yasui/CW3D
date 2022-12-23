#include "RunJumpAttack1State.h"

ActionGame::RunJumpAttack1State::RunJumpAttack1State(Parameter param)
	: AttackBaseState()
	, m_Parameter(param)
	, collideStartFlg(false)
{
}

void ActionGame::RunJumpAttack1State::Start()
{
	m_Attack1Action = Actor()->GetAction<RunJumpAttack1Action>(GetKey());
	AttackBaseState::Start();
	m_Attack1Action->Start();
	//“–‚½‚è”»’è—p‚Ì’eì¬
	CreateShotAABB();

}

void ActionGame::RunJumpAttack1State::Execution()
{

	for (auto& shot : m_pShots)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
		if (m_CurrentTime >= m_Parameter.CollideStartFrameTime && !collideStartFlg)
		{
			shot->SetEnableCollider(true);
		}
	}
	if (m_CurrentTime >= m_Parameter.CollideStartFrameTime && !collideStartFlg)
	{
		CreateEffect();
		collideStartFlg = true;
	}


	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		ChangeState(STATE_KEY_FALL);
	}
	else if (m_NextInputFlg)
	{
		if (Actor()->GetAnimationState()->GetTime() > m_Parameter.NextInputFrameTime)
		{
			ChangeState(STATE_KEY_RUNJUMPATTACK2);
		}
	}
	AttackBaseState::Execution();
}

void ActionGame::RunJumpAttack1State::InputExecution()
{

	if (Input()->IsPush(INPUT_KEY_ATTACK))
	{
		m_NextInputFlg = true;
	}

	AttackBaseState::InputExecution();
}

void ActionGame::RunJumpAttack1State::End()
{
	AttackBaseState::End();
	m_Attack1Action->End();
}

void ActionGame::RunJumpAttack1State::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::RunJumpAttack1State::GetKey() const
{
	return STATE_KEY_RUNJUMPATTACK1;
}
