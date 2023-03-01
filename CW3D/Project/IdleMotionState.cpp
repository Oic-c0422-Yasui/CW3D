#include "IdleMotionState.h"

ActionGame::CIdleMotionState::CIdleMotionState()
	: CState()
{
}

void ActionGame::CIdleMotionState::Start()
{
	action_ = Actor()->GetAction<IdleMotionAction>(GetKey());
	action_->Start();

}

void ActionGame::CIdleMotionState::Execution()
{
	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		ChangeState(STATE_KEY_IDLE);
	}
}

void ActionGame::CIdleMotionState::InputExecution()
{
	float scale = TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());
	//�^�C���X�P�[����0�ȉ��̏ꍇ�A���͂��󂯕t���Ȃ�
	if (scale <= 0.0f)
	{
		return;
	}

	//�L�[�{�[�h�ł̈ړ�
	if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) ||
		Input()->IsPress(INPUT_KEY_HORIZONTAL) ||
		Input()->IsNegativePress(INPUT_KEY_VERTICAL) ||
		Input()->IsPress(INPUT_KEY_VERTICAL))
	{
		ChangeState(STATE_KEY_MOVE);
	}

	if (Input()->IsPush(INPUT_KEY_JUMP))
	{
		ChangeState(STATE_KEY_JUMP);
	}

	if (Input()->IsPush(INPUT_KEY_ATTACK))
	{
		ChangeState(STATE_KEY_ATTACK1);
	}

	
	//�Ή������X�L���̃{�^����������Ă����炻�̃X�L���̃X�e�[�g�Ɉړ�
	for (int i = 0; i < Actor()->GetSkillController()->GetCount(); i++)
	{
		if (!Actor()->GetSkillController()->GetSkill(i)->IsCanUse() || Actor()->GetSkillController()->GetSkill(i)->GetState() == NULL)
		{
			continue;
		}
		if (Input()->IsPush(Actor()->GetSkillController()->GetSkill(i)->GetButton()))
		{

			Actor()->GetSkillController()->GetSkill(i)->Start();
			ChangeState(Actor()->GetSkillController()->GetSkill(i)->GetState());
			break;
		}
	}
}

void ActionGame::CIdleMotionState::End()
{
}

void ActionGame::CIdleMotionState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CIdleMotionState::GetKey() const
{
	return STATE_KEY_IDLE_MOTION;
}
