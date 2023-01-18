#include "JumpAttack1State.h"

ActionGame::JumpAttack1State::JumpAttack1State(Parameter param)
	: AttackBaseState()
	, m_Parameter(param)
	, collideStartFlg(false)
{
}

void ActionGame::JumpAttack1State::Start()
{
	m_JumpAttack1Action = Actor()->GetAction<JumpAttack1Action>(GetKey());
	AttackBaseState::Start();
	m_JumpAttack1Action->Start();
	collideStartFlg = false;

	//“–‚½‚è”»’è—p‚Ì’eì¬
	CreateShotAABB();

}

void ActionGame::JumpAttack1State::Execution()
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
	AttackBaseState::Execution();
}

void ActionGame::JumpAttack1State::InputExecution()
{
	AttackBaseState::InputExecution();
}

void ActionGame::JumpAttack1State::End()
{
	AttackBaseState::End();
}

void ActionGame::JumpAttack1State::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::JumpAttack1State::GetKey() const
{
	return STATE_KEY_JUMP_ATTACK1;
}
