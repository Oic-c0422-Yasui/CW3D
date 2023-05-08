#include "Attack3State.h"

ActionGame::CAttack3State::CAttack3State(Parameter param)
	: CAttackBaseState()
	, parameter_(param)
	, isCollideStartFirst_(false)
	, isCollideStartSecond_(false)
{
}

void ActionGame::CAttack3State::Start() 
{
	action_ = Actor()->GetAction<CAttack3Action>(GetKey());

	CAttackBaseState::Start();

	action_->Start();
	isCollideStartFirst_ = false;
	isCollideStartSecond_ = false;
	//“–‚½‚è”»’è—p‚Ì’eì¬
	CreateShotAABB();

}

void ActionGame::CAttack3State::Execution() 
{

	for (auto& shot : shots_)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
		if ((currentTime_ >= parameter_.CollideFirstStartTime && !isCollideStartFirst_)
			|| (currentTime_ >= parameter_.CollideSecondStartTime && !isCollideStartSecond_))
		{
			shot->SetEnableCollider(true);
			if (currentTime_ >= parameter_.CollideFirstStartTime && !isCollideStartFirst_)
			{
				action_->Execution();

			}

		}
		else if (shot->IsEnableCollider())
		{
			shot->SetEnableCollider(false);
		}

	}
	if (currentTime_ >= parameter_.CollideFirstStartTime && !isCollideStartFirst_)
	{
		isCollideStartFirst_ = true;
	}
	if (currentTime_ >= parameter_.CollideSecondStartTime && !isCollideStartSecond_)
	{
		isCollideStartSecond_ = true;
	}
	;

	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		ChangeState(STATE_KEY_IDLE);
	}
	CAttackBaseState::Execution();
}

void ActionGame::CAttack3State::InputExecution() 
{
	CAttackBaseState::InputExecution();
}

void ActionGame::CAttack3State::End() 
{
	CAttackBaseState::End();
}

void ActionGame::CAttack3State::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CAttack3State::GetKey() const
{
	return STATE_KEY_ATTACK3;
}

