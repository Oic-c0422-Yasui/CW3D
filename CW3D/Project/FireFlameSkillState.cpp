#include "FireFlameSkillState.h"
#include "CameraController.h"
#include "FollowFixedCamera.h"


ActionGame::CFireFlameSkillState::CFireFlameSkillState(Parameter param)
	: CAttackBaseState()
	, parameter_(param)
	, isLanding_(false)
	, isStartCollide_(false)
{
}

void ActionGame::CFireFlameSkillState::Start()
{
	nonGravityAction_ = Actor()->GetAction<CNoneGravityAction>(GetKey());
	fallAction_ = Actor()->GetAction<CFallAction>(GetKey() + STATE_KEY_FALL);

	currentChargeTime_ = 0.0f;
	isStartCollide_ = false;
	isLanding_ = false;
	CAttackBaseState::Start();
	nonGravityAction_->Start();
	
	CreateShotAABB();
	CreateEffect(parameter_.ChargeEffectStatus);

	SetArmorLevel(parameter_.armorLevel);
	
	for (auto& shot : shots_)
	{
		auto skillDamage = Actor()->GetSkillController()->GetSkill(SKILL_KEY_8)->GetDamage();
		auto damage = MyUtil::CalculateAtk(shot->GetDamage(), skillDamage);
		shot->SetDamage(damage);
	}

	MyUtil::ANIM_DATA_ARRAY anims(
		{
			{0.0f,0.0f},
			{parameter_.ChargeTime,0.0f},
			{parameter_.ChargeTime,TimeScaleControllerInstance.GetTimeScale()},
		}
	);
	TimeScaleControllerInstance.SetOtherTimeScale(Actor()->GetType(), anims);


	
	Vector3 pos(0, 12, -12);
	Vector3 lookPos(0, 1, 0);

	CameraPtr camera;
	camera = std::make_shared<CFollowFixedCamera>(Actor()->GetPosition(), Actor()->GetPosition(), pos, lookPos);
	CameraControllerInstance.SetCamera(camera, 5.0f, MyUtil::EASING_TYPE::IN_SINE, 0.3f, MyUtil::EASING_TYPE::IN_SINE, 1.5f);
}

void ActionGame::CFireFlameSkillState::Execution()
{
	if (currentChargeTime_ < parameter_.ChargeTime)
	{
		currentChargeTime_ += CUtilities::GetFrameSecond() * 
							TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());
		if (currentChargeTime_ >= parameter_.ChargeTime)
		{
			fallAction_->Start();
			nonGravityAction_->End();
			
		}
		return;
	}
	else
	{
		fallAction_->Execution();
	}
	
	if (IsFly())
	{
		return;
	}
	if (!isLanding_)
	{
		CreateEffect();
		SettingCamera();
		isLanding_ = true;
	}
	

	for (auto& shot : shots_)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
		if (currentTime_ >= parameter_.CollideStartTime && !isStartCollide_)
		{
			shot->SetEnableCollider(true);
		}
		if (currentTime_ > parameter_.CollideEndTime)
		{
			if (shot->IsEnableCollider())
			{
				shot->SetEnableCollider(false);
			}
		}

	}
	if (currentTime_ >= parameter_.CollideStartTime && !isStartCollide_)
	{
		isStartCollide_ = true;
	}


	if (Actor()->GetAnimationState()->IsEndMotion() &&
		currentTime_ > parameter_.EndTime)
	{
		ChangeState(STATE_KEY_IDLE);
	}

	CAttackBaseState::Execution();
}

void ActionGame::CFireFlameSkillState::InputExecution()
{
	CAttackBaseState::InputExecution();
}

void ActionGame::CFireFlameSkillState::End()
{
	nonGravityAction_->End();
	fallAction_->End();
	CAttackBaseState::End();
}

void ActionGame::CFireFlameSkillState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CFireFlameSkillState::GetKey() const
{
	return STATE_KEY_FIREFLAME_SKILL;
}

void ActionGame::CFireFlameSkillState::SettingCamera()
{
	MyUtil::ANIM_V3_DATA_ARRAY animPos(
		{
			{0.0f,Vector3(0,10,-12)},
			{0.0f,Vector3(0,10,-12),MyUtil::EASING_TYPE::OUT_SINE},
			{0.3f,Vector3(0,12,-30),MyUtil::EASING_TYPE::OUT_SINE},
		}
	);
	MyUtil::ANIM_V3_DATA_ARRAY animLookPos(
		{
			{0.0f,Vector3(0, 1, 0)},
			{0.0f,Vector3(0, 1, 0)},
			{0.0f,Vector3(0, 1, 0)},
		}
	);
	Vector3 pos(0, 10, -12);
	Vector3 lookPos(0, 1, 0);

	size_t animCount = animPos.size();

	CameraPtr camera;
	camera = std::make_shared<CFollowFixedCamera>(Actor()->GetPosition(), Actor()->GetPosition(), pos, lookPos);
	camera->SetAnimation(animPos, animLookPos);
	CameraControllerInstance.SetCamera(camera, 0.4f, MyUtil::EASING_TYPE::IN_SINE, 0.3f, MyUtil::EASING_TYPE::IN_SINE, 2.0f);
}
