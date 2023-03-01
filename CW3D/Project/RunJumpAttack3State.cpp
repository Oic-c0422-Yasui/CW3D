#include "RunJumpAttack3State.h"

ActionGame::CRunJumpAttack3State::CRunJumpAttack3State(Parameter param)
	: CAttackBaseState()
	, parameter_(param)
	, isStartCollide_(false)
{
}

void ActionGame::CRunJumpAttack3State::Start()
{
	action_ = Actor()->GetAction<CRunJumpAttack3Action>(GetKey());
	CAttackBaseState::Start();
	isStartCollide_ = false;
	action_->Start();
	//“–‚½‚è”»’è—p‚Ì’eì¬
	CreateShotAABB();

}

void ActionGame::CRunJumpAttack3State::Execution()
{
	for (auto& shot : shots_)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
		if (currentTime_ >= parameter_.CollideFirstStartFrameTime && !isStartCollide_)
		{
			action_->Execution();
			action_->Jump();

		}
		else if (currentTime_ >= parameter_.CollideSecondStartFrameTime && shot->IsEnableCollider())
		{
			shot->SetEnableCollider(false);
		}

	}
	if (currentTime_ >= parameter_.CollideFirstStartFrameTime && !isStartCollide_)
	{
		isStartCollide_ = true;
	}

	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		ChangeState(STATE_KEY_FALL);
	}
	CAttackBaseState::Execution();
}

void ActionGame::CRunJumpAttack3State::InputExecution()
{
	CAttackBaseState::InputExecution();
}

void ActionGame::CRunJumpAttack3State::End()
{
	CAttackBaseState::End();
	action_->End();
}

void ActionGame::CRunJumpAttack3State::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CRunJumpAttack3State::GetKey() const
{
	return STATE_KEY_RUN_JUMP_ATTACK3;
}
