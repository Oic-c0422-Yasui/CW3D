#include "TackleAttackState.h"



ActionGame::CTackleAttackState::CTackleAttackState(Parameter param)
	:CAttackBaseState()
	, parameter_(param)
	, isStartCollide_(false)
	, currentReadyTime_(0.0f)
{
}

void ActionGame::CTackleAttackState::Start()
{
	readyAction_ = Actor()->GetAction<CIdleAction>(GetKey());
	moveAction_ = Actor()->GetAction<CMoveAction>(GetKey() + STATE_KEY_MOVE);
	
	CreateShotAABB();
	
	currentReadyTime_ = 0.0f;
	isStartCollide_ = false;
	readyAction_->Start();

}

void ActionGame::CTackleAttackState::Execution()
{
	if (currentReadyTime_ < parameter_.CollideStartTime)
	{
		currentReadyTime_ += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());
		if (currentReadyTime_ >= parameter_.CollideStartTime)
		{
			CAttackBaseState::Start();
			moveAction_->Start();
			CreateEffect();
		}

		return;
	}

	for (auto& shot : shots_)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
		if (!isStartCollide_)
		{
			shot->SetEnableCollider(true);
		}

	}
	for (auto& effect : effects_)
	{
		EffectControllerInstance.SetPosition(effect->GetHandle(), Actor()->GetPosition() + effect->GetOffset());
	}
	if (!isStartCollide_)
	{
		isStartCollide_ = true;
	}

	if (currentTime_ > 0.6f)
	{
		ChangeState(STATE_KEY_IDLE);
	}

	CAttackBaseState::Execution();
}

void ActionGame::CTackleAttackState::InputExecution()
{
	CAttackBaseState::InputExecution();
}

void ActionGame::CTackleAttackState::End()
{
	CAttackBaseState::End();
	readyAction_->End();
	moveAction_->End();
}

void ActionGame::CTackleAttackState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CTackleAttackState::GetKey() const
{
	return STATE_KEY_TACKLE_ATTACK;
}
