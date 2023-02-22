#include "IdleState.h"

ActionGame::IdleState::IdleState(Parameter param)
	: State()
	, time_(0.0f)
	, m_Parameter(param)
{
}

void ActionGame::IdleState::Start()
{
	m_IdleAction = Actor()->GetAction<IdleAction>(GetKey());
	time_ = 0.0f;
	m_IdleAction->Start();
}

void ActionGame::IdleState::Execution()
{
	if (time_ < m_Parameter.idleTime)
	{
		time_ += CUtilities::GetFrameSecond();
	}
	else
	{
		ChangeState(STATE_KEY_IDLE_MOTION);

	}
}

void ActionGame::IdleState::InputExecution()
{
	float scale = TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());
	//タイムスケールが0以下の場合、入力を受け付けない
	if (scale <= 0.0f)
	{
		return;
	}

	if (Input()->IsNegativeDoublePush(INPUT_KEY_HORIZONTAL) || Input()->IsDoublePush(INPUT_KEY_HORIZONTAL) ||
		Input()->IsNegativeDoublePush(INPUT_KEY_VERTICAL) || Input()->IsDoublePush(INPUT_KEY_VERTICAL))
	{
		ChangeState(STATE_KEY_RUN);
	}
	//キーボードでの移動
	else if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) || Input()->IsPress(INPUT_KEY_HORIZONTAL) ||
		Input()->IsNegativePress(INPUT_KEY_VERTICAL) || Input()->IsPress(INPUT_KEY_VERTICAL))
	{
		ChangeState(STATE_KEY_MOVE);
	}

	if (Input()->IsPush(INPUT_KEY_JUMP))
	{
		ChangeState(STATE_KEY_JUMP, STATE_KEY_MOVE);
	}

	if (Input()->IsPush(INPUT_KEY_ATTACK))
	{
		ChangeState(STATE_KEY_ATTACK1, STATE_KEY_MOVE);
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
			ChangeState(Actor()->GetSkillController()->GetSkill(i)->GetState(), STATE_KEY_MOVE);
			break;
		}
	}

}

void ActionGame::IdleState::End()
{
}

void ActionGame::IdleState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::IdleState::GetKey() const
{
	return STATE_KEY_IDLE;
}

