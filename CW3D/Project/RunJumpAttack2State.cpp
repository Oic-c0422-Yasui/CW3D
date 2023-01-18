#include "RunJumpAttack2State.h"

ActionGame::RunJumpAttack2State::RunJumpAttack2State(Parameter param)
	: AttackBaseState()
	, m_Parameter(param)
{
}

void ActionGame::RunJumpAttack2State::Start()
{
	m_Attack2Action = Actor()->GetAction<RunJumpAttack2Action>(GetKey());
	AttackBaseState::Start();
	m_Attack2Action->Start();
	//当たり判定用の弾作成
	CreateShotAABB();
}

void ActionGame::RunJumpAttack2State::Execution()
{

	for (auto& shot : m_pShots)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
	}

	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		ChangeState(STATE_KEY_FALL);
	}
	if (m_NextInputFlg)
	{
		if (m_CurrentTime > m_Parameter.NextInputFrameTime)
		{
			ChangeState(STATE_KEY_RUN_JUMP_ATTACK3);
		}
	}
	AttackBaseState::Execution();
}

void ActionGame::RunJumpAttack2State::InputExecution()
{
	float scale = TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());
	//タイムスケールが0以下の場合、入力を受け付けない
	if (scale <= 0.0f)
	{
		return;
	}
	if (Input()->IsPush(INPUT_KEY_ATTACK))
	{
		m_NextInputFlg = true;
	}

	AttackBaseState::InputExecution();
}

void ActionGame::RunJumpAttack2State::End()
{
	AttackBaseState::End();
	m_Attack2Action->End();
}

void ActionGame::RunJumpAttack2State::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::RunJumpAttack2State::GetKey() const
{
	return STATE_KEY_RUN_JUMP_ATTACK2;
}
