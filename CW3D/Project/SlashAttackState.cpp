#include "SlashAttackState.h"

ActionGame::CSlashAttackState::CSlashAttackState(Parameter param)
	: CAttackBaseState()
	, parameter_(param)
	, isCollideStartFirst_(false)
	, isCollideStartSecond_(false)
	, isFirstAnimChange_(false)
{
}

void ActionGame::CSlashAttackState::Start()
{
	firstAction_ = Actor()->GetAction<CAttack3Action>(GetKey());
	secondAction_ = Actor()->GetAction<CAttack1Action>(GetKey() + STATE_KEY_ATTACK1);

	CAttackBaseState::Start();

	firstAction_->Start();
	isCollideStartFirst_ = false;
	isCollideStartSecond_ = false;
	isFirstAnimChange_ = false;
	//“–‚½‚è”»’è—p‚Ì’eì¬
	CreateShotAABB();
}

void ActionGame::CSlashAttackState::Execution()
{
	for (auto& shot : shots_)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
		if ((currentTime_ >= parameter_.CollideFirstStartTime && !isCollideStartFirst_)
			|| (currentTime_ >= parameter_.CollideSecondStartTime && !isCollideStartSecond_))
		{
			shot->SetEnableCollider(true);
		}
		else if (shot->IsEnableCollider())
		{
			shot->SetEnableCollider(false);
		}
	}
	if (currentTime_ >= parameter_.CollideFirstStartTime && !isCollideStartFirst_)
	{
		CreateEffect();
	}
	else if (currentTime_ >= parameter_.AnimChangeTime && !isFirstAnimChange_)
	{
		CreateEffect();
		secondAction_->Start();
		firstAction_->Execution();
	}

	for (auto& effect : effects_)
	{
		EffectControllerInstance.SetPosition(effect->GetHandle(), Actor()->GetPosition() + parameter_.EffectStatus.offset);
	}


	if (currentTime_ >= parameter_.CollideFirstStartTime && !isCollideStartFirst_)
	{
		isCollideStartFirst_ = true;
	}
	else if (currentTime_ >= parameter_.AnimChangeTime && !isFirstAnimChange_)
	{
		isFirstAnimChange_ = true;
	}
	else if (currentTime_ >= parameter_.CollideSecondStartTime && !isCollideStartSecond_)
	{
		isCollideStartSecond_ = true;
	}

	if (currentTime_ >= parameter_.EndTime)
	{
		ChangeState(STATE_KEY_IDLE);
	}
	CAttackBaseState::Execution();
}

void ActionGame::CSlashAttackState::InputExecution()
{
	CAttackBaseState::InputExecution();
}

void ActionGame::CSlashAttackState::End()
{
	CAttackBaseState::End();
	firstAction_->End();
	secondAction_->End();
}

void ActionGame::CSlashAttackState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CSlashAttackState::GetKey() const
{
	return STATE_KEY_SLASH_ATTACK;
}
