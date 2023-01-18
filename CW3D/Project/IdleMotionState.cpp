#include "IdleMotionState.h"

ActionGame::IdleMotionState::IdleMotionState()
	: State()
{
}

void ActionGame::IdleMotionState::Start()
{
	m_IdleMotionAction = Actor()->GetAction<IdleMotionAction>(GetKey());
	m_IdleMotionAction->Start();

}

void ActionGame::IdleMotionState::Execution()
{
	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		ChangeState(STATE_KEY_IDLE);
	}
}

void ActionGame::IdleMotionState::InputExecution()
{
	float scale = TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());
	//タイムスケールが0以下の場合、入力を受け付けない
	if (scale <= 0.0f)
	{
		return;
	}

	//キーボードでの移動
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

	
	//対応したスキルのボタンが押されていたらそのスキルのステートに移動
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

void ActionGame::IdleMotionState::End()
{
}

void ActionGame::IdleMotionState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::IdleMotionState::GetKey() const
{
	return STATE_KEY_IDLE_MOTION;
}
