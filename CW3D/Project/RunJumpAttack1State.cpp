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
	//当たり判定用の弾作成
	CreateShotAABB();

}

void ActionGame::RunJumpAttack1State::Execution()
{

	for (auto& shot : m_pShots)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
		if (currentTime_ >= m_Parameter.CollideStartFrameTime && !collideStartFlg)
		{
			shot->SetEnableCollider(true);
		}
	}
	if (currentTime_ >= m_Parameter.CollideStartFrameTime && !collideStartFlg)
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
			ChangeState(STATE_KEY_RUN_JUMP_ATTACK2);
		}
	}
	AttackBaseState::Execution();
}

void ActionGame::RunJumpAttack1State::InputExecution()
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
	return STATE_KEY_RUN_JUMP_ATTACK1;
}
