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
	// 落下状態への移行
	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		ChangeState(STATE_KEY_IDLE);
	}
}

void ActionGame::CRunLandingState::InputExecution()
{
	//タイムスケールが0以下の場合、入力を受け付けない
	if (IsTimeScaleZero())
	{
		return;
	}

	//左右で移動
	if (IsPressMoveKey())
	{
		ChangeState(STATE_KEY_RUN);
	}

	if (Input()->IsPush(INPUT_KEY_ATTACK))
	{
		ChangeState(STATE_KEY_ATTACK1);
	}

	//対応したスキルのボタンが押されていたらそのスキルのステートに移動
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
