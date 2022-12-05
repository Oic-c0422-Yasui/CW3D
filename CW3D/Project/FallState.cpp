#include "FallState.h"

ActionGame::FallState::FallState()
	: State()
{
}

void ActionGame::FallState::Start() 
{
	m_FallAction = Actor()->GetAction<FallAction>(GetKey());
	m_FallAction->Start();

}

void ActionGame::FallState::Execution()
{
	m_FallAction->Execution();
	// 落下状態への移行
	if (Actor()->GetVelocity()->GetVelocityY() <= 0.0f &&
		Actor()->GetTransform()->GetPositionY() <= 0)
	{
		ChangeState(STATE_KEY_LANDING);
	}
}

void ActionGame::FallState::InputExecution()
{
	//左右で移動

	if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) ||
		Input()->IsPress(INPUT_KEY_HORIZONTAL) ||
		Input()->IsNegativePress(INPUT_KEY_VERTICAL) ||
		Input()->IsPress(INPUT_KEY_VERTICAL))
	{
		m_FallAction->Acceleration(Input()->GetAxis(INPUT_KEY_HORIZONTAL), -(Input()->GetAxis(INPUT_KEY_VERTICAL)));
	}


	if (Input()->IsPush(INPUT_KEY_ATTACK))
	{
		ChangeState(STATE_KEY_JUMPATTACK1);
	}

	//対応したスキルのボタンが押されていたらそのスキルのステートに移動
	for (int i = 0; i < Actor()->GetSkillController()->GetCount(); i++)
	{
		if (!Actor()->GetSkillController()->GetSkill(i)->IsCanUse() || Actor()->GetSkillController()->GetSkill(i)->GetFlyState() == NULL)
		{
			continue;
		}
		if (Input()->IsPush(Actor()->GetSkillController()->GetSkill(i)->GetButton()))
		{

			Actor()->GetSkillController()->GetSkill(i)->Start();
			ChangeState(Actor()->GetSkillController()->GetSkill(i)->GetFlyState());
			break;
		}
	}

}

void ActionGame::FallState::End()
{
}

void ActionGame::FallState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::FallState::GetKey() const
{
	return STATE_KEY_FALL;
}