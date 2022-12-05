#include "RunJumpAttack3State.h"

ActionGame::RunJumpAttack3State::RunJumpAttack3State(Parameter param)
	: AttackBaseState()
	, m_Parameter(param)
	, collideStartFlg(false)
{
}

void ActionGame::RunJumpAttack3State::Start()
{
	m_Attack3Action = Actor()->GetAction<RunJumpAttack3Action>(GetKey());
	AttackBaseState::Start();
	collideStartFlg = false;
	m_Attack3Action->Start();
	//“–‚½‚è”»’è—p‚Ì’eì¬
	CreateShotAABB();

}

void ActionGame::RunJumpAttack3State::Execution()
{
	for (auto& shot : m_pShots)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
		if (m_CurrentTime >= m_Parameter.CollideFirstStartFrameTime && !collideStartFlg)
		{
			m_Attack3Action->Execution();
			m_Attack3Action->Jump();

		}
		else if (m_CurrentTime >= m_Parameter.CollideSecondStartFrameTime && shot->GetCollideFlg())
		{
			shot->SetCollideFlg(false);
		}

	}
	if (m_CurrentTime >= m_Parameter.CollideFirstStartFrameTime && !collideStartFlg)
	{
		collideStartFlg = true;
	}

	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		ChangeState(STATE_KEY_FALL);
	}
	AttackBaseState::Execution();
}

void ActionGame::RunJumpAttack3State::InputExecution()
{
	AttackBaseState::InputExecution();
}

void ActionGame::RunJumpAttack3State::End()
{
	AttackBaseState::End();
	m_Attack3Action->End();
}

void ActionGame::RunJumpAttack3State::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::RunJumpAttack3State::GetKey() const
{
	return STATE_KEY_RUNJUMPATTACK3;
}
