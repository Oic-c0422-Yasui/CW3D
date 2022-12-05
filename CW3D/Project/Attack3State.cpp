#include "Attack3State.h"

ActionGame::Attack3State::Attack3State(Parameter param)
	: AttackBaseState()
	, m_Parameter(param)
	, collideFirstStartFlg(false)
	, collideSecondStartFlg(false)
{
}

void ActionGame::Attack3State::Start() 
{
	m_Attack3Action = Actor()->GetAction<Attack3Action>(GetKey());

	AttackBaseState::Start();

	m_Attack3Action->Start();
	collideFirstStartFlg = false;
	collideSecondStartFlg = false;
	//“–‚½‚è”»’è—p‚Ì’eì¬
	CreateShotAABB();

}

void ActionGame::Attack3State::Execution() 
{

	for (auto& shot : m_pShots)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
		if ((m_CurrentTime >= m_Parameter.CollideFirstStartFrameTime && !collideFirstStartFlg)
			|| (m_CurrentTime >= m_Parameter.CollideSecondStartFrameTime && !collideSecondStartFlg))
		{
			shot->SetCollideFlg(true);
			if (m_CurrentTime >= m_Parameter.CollideFirstStartFrameTime && !collideFirstStartFlg)
			{
				m_Attack3Action->Execution();

			}

		}
		else if (shot->GetCollideFlg())
		{
			shot->SetCollideFlg(false);
		}

	}
	if (m_CurrentTime >= m_Parameter.CollideFirstStartFrameTime && !collideFirstStartFlg)
	{
		collideFirstStartFlg = true;
	}
	if (m_CurrentTime >= m_Parameter.CollideSecondStartFrameTime && !collideSecondStartFlg)
	{
		collideSecondStartFlg = true;
	}
	;

	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		ChangeState(STATE_KEY_IDLE);
	}
	AttackBaseState::Execution();
}

void ActionGame::Attack3State::InputExecution() 
{
	AttackBaseState::InputExecution();
}

void ActionGame::Attack3State::End() 
{
	AttackBaseState::End();
}

void ActionGame::Attack3State::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::Attack3State::GetKey() const
{
	return STATE_KEY_ATTACK3;
}

