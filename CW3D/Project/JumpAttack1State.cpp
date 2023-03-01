#include "JumpAttack1State.h"

ActionGame::CJumpAttack1State::CJumpAttack1State(Parameter param)
	: CAttackBaseState()
	, parameter_(param)
	, isStartCollide_(false)
{
}

void ActionGame::CJumpAttack1State::Start()
{
	action_ = Actor()->GetAction<CJumpAttack1Action>(GetKey());
	CAttackBaseState::Start();
	action_->Start();
	isStartCollide_ = false;

	//“–‚½‚è”»’è—p‚Ì’eì¬
	CreateShotAABB();

}

void ActionGame::CJumpAttack1State::Execution()
{

	for (auto& shot : shots_)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
		if (currentTime_ >= parameter_.CollideStartFrameTime && !isStartCollide_)
		{
			shot->SetEnableCollider(true);

		}
	}

	if (currentTime_ >= parameter_.CollideStartFrameTime && !isStartCollide_)
	{
		CreateEffect();
		isStartCollide_ = true;
	}


	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		ChangeState(STATE_KEY_FALL);
	}
	CAttackBaseState::Execution();
}

void ActionGame::CJumpAttack1State::InputExecution()
{
	CAttackBaseState::InputExecution();
}

void ActionGame::CJumpAttack1State::End()
{
	CAttackBaseState::End();
}

void ActionGame::CJumpAttack1State::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CJumpAttack1State::GetKey() const
{
	return STATE_KEY_JUMP_ATTACK1;
}
