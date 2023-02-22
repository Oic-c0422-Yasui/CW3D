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
	//当たり判定用の弾作成
	CreateShotAABB();

}

void ActionGame::RunJumpAttack3State::Execution()
{
	for (auto& shot : m_pShots)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
		if (currentTime_ >= m_Parameter.CollideFirstStartFrameTime && !collideStartFlg)
		{
			m_Attack3Action->Execution();
			m_Attack3Action->Jump();

		}
		else if (currentTime_ >= m_Parameter.CollideSecondStartFrameTime && shot->IsEnableCollider())
		{
			shot->SetEnableCollider(false);
		}

	}
	if (currentTime_ >= m_Parameter.CollideFirstStartFrameTime && !collideStartFlg)
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
	return STATE_KEY_RUN_JUMP_ATTACK3;
}
