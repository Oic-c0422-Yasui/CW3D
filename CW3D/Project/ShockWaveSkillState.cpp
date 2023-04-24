#include "ShockWaveSkillState.h"
#include "CameraController.h"
#include "FixedCamera.h"

ActionGame::CShockWaveSkillState::CShockWaveSkillState(Parameter param)
	: CAttackBaseState()
	, parameter_(param)
	, isStartCollide_(false)
{
}

void ActionGame::CShockWaveSkillState::Start()
{
	action_ = Actor()->GetAction<CShockWaveSkillAction>(GetKey());
	isStartCollide_ = false;
	CAttackBaseState::Start();
	action_->Start();
	CreateShotAABB();
	CreateEffect();
	for (auto& shot : shots_)
	{
		auto skillDamage = Actor()->GetSkillController()->GetSkill(SKILL_KEY_3)->GetDamage();
		auto damage = MyUtil::CalculateAtk(shot->GetDamage(), skillDamage);
		shot->SetDamage(damage);
	}

	MyUtil::ANIM_DATA_ARRAY anims(
		{
			{0.0f,0.0f},
			{0.8f,0.0f},
			{0.8f,TimeScaleControllerInstance.GetTimeScale()},
		}
	);
	TimeScaleControllerInstance.SetOtherTimeScale(Actor()->GetType(), anims);


	MyUtil::ANIM_V3_DATA_ARRAY animPos(
		{
			{0.0f,Vector3(-7,2,-2)},
			{0.25f,Vector3(-7,2,-2),MyUtil::EASING_TYPE::OUT_SINE},
			{0.30f,Vector3(-25,2,-2),MyUtil::EASING_TYPE::OUT_SINE},
		}
	);
	MyUtil::ANIM_V3_DATA_ARRAY animLookPos(
		{
			{0.0f,Vector3(2, 1, 2)},
			{1.0f,Vector3(2, 1, 2)},
			{1.0f,Vector3(2, 1, 2)},
		}
	);
	Vector3 pos(-7, 2, -2);
	Vector3 lookPos(2, 1, 2);

	size_t animCount = animPos.size();
	//”½“]ˆ—
	if (Actor()->IsReverse())
	{
		pos.x *= -1;
		lookPos.x *= -1;
		for (size_t i = 0; i < animCount; i++)
		{
			animPos[i].Value.x *= -1;
			animLookPos[i].Value.x *= -1;
		}
	}
	CameraPtr camera;
	camera = std::make_shared<CFixedCamera>(Actor()->GetPosition(), Actor()->GetPosition(), pos, lookPos);
	camera->SetAnimation(animPos, animLookPos);
	CameraControllerInstance.SetCamera(camera, 1, MyUtil::EASING_TYPE::IN_SINE, 0.3f, MyUtil::EASING_TYPE::IN_SINE, 0.5f);

}

void ActionGame::CShockWaveSkillState::Execution()
{

	for (auto& shot : shots_)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
		if (currentTime_ >= parameter_.CollideStartFrameTime && !isStartCollide_)
		{
			shot->SetEnableCollider(true);
		}
		if (currentTime_ > parameter_.CollideEndFrameTime)
		{
			if (shot->IsEnableCollider())
			{
				shot->SetEnableCollider(false);
			}
		}

	}
	if (currentTime_ >= parameter_.CollideStartFrameTime && !isStartCollide_)
	{
		isStartCollide_ = true;
	}


	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		auto state = IsFly() ? STATE_KEY_FALL : STATE_KEY_IDLE;

		ChangeState(state);
	}

	CAttackBaseState::Execution();
}

void ActionGame::CShockWaveSkillState::InputExecution()
{
	CAttackBaseState::InputExecution();
}

void ActionGame::CShockWaveSkillState::End()
{
	action_->End();
	CAttackBaseState::End();
}

void ActionGame::CShockWaveSkillState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::CShockWaveSkillState::GetKey() const
{
	return STATE_KEY_SHOCKWAVE_SKILL;
}
