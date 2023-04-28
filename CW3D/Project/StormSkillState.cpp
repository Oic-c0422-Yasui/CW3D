#include "StormSkillState.h"
#include "FollowFixedCamera.h"
#include "CameraController.h"
#include "ParameterDefine.h"

ActionGame::CStormSkillState::CStormSkillState(Parameter param)
	: CAttackBaseState()
	, parameter_(param)
	, isContinue_(false)
	, attackTime_(0.0f)
{
}

void ActionGame::CStormSkillState::Start()
{
	action_ = Actor()->GetAction<CStormSkillAction>(GetKey());

	attackTime_ = 0.0f;

	isContinue_ = true;

	SetArmorLevel(parameter_.armorLevel);

	CAttackBaseState::Start();
	action_->Start();
	CreateShotAABB();
	CreateEffect();
	for (auto& shot : shots_)
	{
		auto skillDamage = Actor()->GetSkillController()->GetSkill(SKILL_KEY_2)->GetDamage();
		auto damage = MyUtil::CalculateAtk(shot->GetDamage(), skillDamage);
		shot->SetDamage(damage);
	}

	
	inputKey_ = Actor()->GetSkillController()->GetSkill(SKILL_KEY_2)->GetButton();

	Vector3 pos(0, 10, -20);
	Vector3 lookPos(0, 3, 0);
	if (Actor()->IsReverse())
	{
		pos.x *= -1;
		lookPos.x *= -1;
	}
	CameraPtr camera;
	camera = std::make_shared<ActionGame::CFollowFixedCamera>(Actor()->GetPosition(), Actor()->GetPosition(), pos, lookPos);
	CameraControllerInstance.SetCamera(camera, 2.3f, MyUtil::EASING_TYPE::IN_SINE, 0.7f, MyUtil::EASING_TYPE::IN_SINE, 0.5f);
}

void ActionGame::CStormSkillState::Execution()
{

	for (auto& shot : shots_)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
		if (attackTime_ >= parameter_.AttackFrequencyFrameTime)
		{
			shot->SetEnableCollider(true);

		}
		else if (shot->IsEnableCollider())
		{
			shot->SetEnableCollider(false);
		}

	}
	if (attackTime_ >= parameter_.AttackFrequencyFrameTime)
	{
		attackTime_ = 0.0f;
	}


	for (auto& effect : effects_)
	{
		EffectControllerInstance.SetPosition(effect->GetHandle(), Actor()->GetPosition() + parameter_.EffectStatus.offset);
	}

	attackTime_ += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());

	if (currentTime_ > parameter_.DurationTime || !isContinue_)
	{
		auto state = IsFly() ? STATE_KEY_FALL : STATE_KEY_IDLE;

		ChangeState(state);
	}

	CAttackBaseState::Execution();
}

void ActionGame::CStormSkillState::InputExecution()
{
	//タイムスケールが0以下の場合、入力を受け付けない
	if (IsTimeScaleZero())
	{
		return;
	}

	//入力猶予時間までキーが押されているなら攻撃を続ける
	if (currentTime_ > parameter_.ContinueTime)
	{
		isContinue_ = Input()->IsPress(inputKey_) ?
						true : false;
	}

	if (IsPressMoveKey())
	{
		action_->Acceleration(Input()->GetAxis(INPUT_KEY_HORIZONTAL), -(Input()->GetAxis(INPUT_KEY_VERTICAL)));
	}

	CAttackBaseState::InputExecution();
}

void ActionGame::CStormSkillState::End()
{
	action_->End();
	CAttackBaseState::End();
	CameraControllerInstance.SetDefault();

}

void ActionGame::CStormSkillState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CStormSkillState::GetKey() const
{
	return STATE_KEY_STORM_SKILL;
}

