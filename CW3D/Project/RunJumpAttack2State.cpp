#include "RunJumpAttack2State.h"

ActionGame::CRunJumpAttack2State::CRunJumpAttack2State(Parameter param)
	: CAttackBaseState()
	, parameter_(param)
{
}

void ActionGame::CRunJumpAttack2State::Start()
{
	action_ = Actor()->GetAction<CRunJumpAttack2Action>(GetKey());
	CAttackBaseState::Start();
	action_->Start();
	//�����蔻��p�̒e�쐬
	CreateShotAABB();
}

void ActionGame::CRunJumpAttack2State::Execution()
{

	for (auto& shot : shots_)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
	}

	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		ChangeState(STATE_KEY_FALL);
	}
	if (isNextInput_)
	{
		if (currentTime_ > parameter_.NextInputFrameTime)
		{
			ChangeState(STATE_KEY_RUN_JUMP_ATTACK3);
		}
	}
	CAttackBaseState::Execution();
}

void ActionGame::CRunJumpAttack2State::InputExecution()
{
	float scale = TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());
	//�^�C���X�P�[����0�ȉ��̏ꍇ�A���͂��󂯕t���Ȃ�
	if (scale <= 0.0f)
	{
		return;
	}
	if (Input()->IsPush(INPUT_KEY_ATTACK))
	{
		isNextInput_ = true;
	}

	CAttackBaseState::InputExecution();
}

void ActionGame::CRunJumpAttack2State::End()
{
	CAttackBaseState::End();
	action_->End();
}

void ActionGame::CRunJumpAttack2State::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CRunJumpAttack2State::GetKey() const
{
	return STATE_KEY_RUN_JUMP_ATTACK2;
}
