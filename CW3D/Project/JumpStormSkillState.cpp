#include "JumpStormSkillState.h"
#include "FollowFixedCamera.h"
#include "CameraController.h"
#include "ParameterDefine.h"

ActionGame::CJumpStormSkillState::CJumpStormSkillState(Parameter param)
	: CAttackBaseState()
	, parameter_(param)
	, isContinue_(false)
	, attackTime_(0.0f)
	, inputKey_()
{
}

void ActionGame::CJumpStormSkillState::Start()
{
	action_ = Actor()->GetAction<CNoneGravityAction>(GetKey());

	attackTime_ = 0.0f;
	isContinue_ = true;

	CAttackBaseState::Start();
	action_->Start();

	SetArmorLevel(parameter_.armorLevel);

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
	CameraPtr camera;
	camera = std::make_shared<ActionGame::CFollowFixedCamera>(Actor()->GetPosition(), Actor()->GetPosition(), pos, lookPos);
	CameraControllerInstance.SetCamera(camera, 2.3f, MyUtil::EASING_TYPE::IN_SINE, 0.7f, MyUtil::EASING_TYPE::IN_SINE, 0.7f);

}

void ActionGame::CJumpStormSkillState::Execution() 
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

void ActionGame::CJumpStormSkillState::InputExecution()
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
		action_->Acceleration(Input()->GetAxis(INPUT_KEY_HORIZONTAL), 
							-(Input()->GetAxis(INPUT_KEY_VERTICAL)));
	}

	CAttackBaseState::InputExecution();
}

void ActionGame::CJumpStormSkillState::End()
{
	action_->End();
	CAttackBaseState::End();

	CameraPtr camera;
	Vector3 pos(0, 10, -20);
	Vector3 lookPos(0, 3, 0);
	
	CameraControllerInstance.SetDefault();
}

void ActionGame::CJumpStormSkillState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CJumpStormSkillState::GetKey() const
{
	return STATE_KEY_JUMP_STORM_SKILL;
}

