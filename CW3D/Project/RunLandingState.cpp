#include "RunLandingState.h"

ActionGame::CRunLandingState::CRunLandingState()
	: CState()
{
}

void ActionGame::CRunLandingState::Start()
{
	action_ = Actor()->GetAction<CRunLandingAction>(GetKey());
	action_->Start();
}

void ActionGame::CRunLandingState::Execution()
{
	action_->Execution();
	// ������Ԃւ̈ڍs
	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		ChangeState(STATE_KEY_IDLE);
	}
}

void ActionGame::CRunLandingState::InputExecution()
{
	float scale = TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());
	//�^�C���X�P�[����0�ȉ��̏ꍇ�A���͂��󂯕t���Ȃ�
	if (scale <= 0.0f)
	{
		return;
	}
	//���E�ňړ�

	if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) ||
		Input()->IsPress(INPUT_KEY_HORIZONTAL) ||
		Input()->IsNegativePress(INPUT_KEY_VERTICAL) ||
		Input()->IsPress(INPUT_KEY_VERTICAL))
	{
		ChangeState(STATE_KEY_RUN);
	}


	if (Input()->IsPush(INPUT_KEY_ATTACK))
	{
		ChangeState(STATE_KEY_ATTACK1);
	}

	//�Ή������X�L���̃{�^����������Ă����炻�̃X�L���̃X�e�[�g�Ɉړ�
	for (int i = 0; i < Actor()->GetSkillController()->GetCount(); i++)
	{
		if (!Actor()->GetSkillController()->GetSkill(i)->CanUseSkill() || Actor()->GetSkillController()->GetSkill(i)->GetState() == NULL)
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

void ActionGame::CRunLandingState::End()
{
}

void ActionGame::CRunLandingState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CRunLandingState::GetKey() const
{
	return STATE_KEY_RUN_LANDING;
}
