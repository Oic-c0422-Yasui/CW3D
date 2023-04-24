#include "BaseState.h"



ActionGame::CBaseState::CBaseState()
	: CState()
{
}

bool ActionGame::CBaseState::IsPressHorizontalKey()
{
	bool isPress = (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) ||
		Input()->IsPress(INPUT_KEY_HORIZONTAL));

	return isPress;
}

bool ActionGame::CBaseState::IsPressVirticalKey()
{
	bool isPress = (Input()->IsNegativePress(INPUT_KEY_VERTICAL) ||
		Input()->IsPress(INPUT_KEY_VERTICAL));

	return isPress;
}

bool ActionGame::CBaseState::IsPressMoveKey()
{
	return IsPressHorizontalKey() || IsPressVirticalKey();
}



bool ActionGame::CBaseState::IsFly()
{
	return Actor()->GetTransform()->GetPositionY() > 0;
}

void ActionGame::CBaseState::ChangeSkillState()
{

	//対応したスキルのボタンが押されていたらそのスキルのステートに移動
	for (size_t i = 0; i < Actor()->GetSkillController()->GetCount(); i++)
	{
		const auto& skill = Actor()->GetSkillController()->GetSkill(i);
		if (!skill->CanUseSkill() || skill->GetState() == nullptr || skill->GetFlyState() == nullptr)
		{
			continue;
		}
		if (Input()->IsPush(skill->GetButton()))
		{
			skill->Start();

			//ステート変更
			SwitchFlyChangeState(skill->GetState(), skill->GetFlyState());

			return;
		}
	}
}

bool ActionGame::CBaseState::IsTimeScaleZero()
{
	auto scale = TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());
	return scale <= 0.0f;
}


void ActionGame::CBaseState::SwitchFlyChangeState(const StateKeyType& state, const StateKeyType& flyState)
{
	const auto& change = IsFly() ? flyState : state;

	ChangeState(change);
}