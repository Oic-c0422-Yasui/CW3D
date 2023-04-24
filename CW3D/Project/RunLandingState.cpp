#include "RunLandingState.h"

ActionGame::CRunLandingState::CRunLandingState()
	: CBaseState()
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
	//�^�C���X�P�[����0�ȉ��̏ꍇ�A���͂��󂯕t���Ȃ�
	if (IsTimeScaleZero())
	{
		return;
	}

	//���E�ňړ�
	if (IsPressMoveKey())
	{
		ChangeState(STATE_KEY_RUN);
	}

	if (Input()->IsPush(INPUT_KEY_ATTACK))
	{
		ChangeState(STATE_KEY_ATTACK1);
	}

	//�Ή������X�L���̃{�^����������Ă����炻�̃X�L���̃X�e�[�g�Ɉړ�
	ChangeSkillState();

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
