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
	//当たり判定用の弾作成
	CreateShotAABB();

}

void ActionGame::Attack3State::Execution() 
{

	for (auto& shot : m_pShots)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
		if ((currentTime_ >= m_Parameter.CollideFirstStartFrameTime && !collideFirstStartFlg)
			|| (currentTime_ >= m_Parameter.CollideSecondStartFrameTime && !collideSecondStartFlg))
		{
			shot->SetEnableCollider(true);
			if (currentTime_ >= m_Parameter.CollideFirstStartFrameTime && !collideFirstStartFlg)
			{
				m_Attack3Action->Execution();

			}

		}
		else if (shot->IsEnableCollider())
		{
			shot->SetEnableCollider(false);
		}

	}
	if (currentTime_ >= m_Parameter.CollideFirstStartFrameTime && !collideFirstStartFlg)
	{
		collideFirstStartFlg = true;
	}
	if (currentTime_ >= m_Parameter.CollideSecondStartFrameTime && !collideSecondStartFlg)
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

