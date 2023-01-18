#include "ShockWaveSkillState.h"
#include "CameraController.h"
#include "FixedCamera.h"

ActionGame::ShockWaveSkillState::ShockWaveSkillState(Parameter param)
	: AttackBaseState()
	, m_Parameter(param)
	, collideStartFlg(false)
{
}

void ActionGame::ShockWaveSkillState::Start()
{
	m_SkillAction = Actor()->GetAction<ShockWaveSkillAction>(GetKey());
	collideStartFlg = false;
	AttackBaseState::Start();
	m_SkillAction->Start();
	CreateShotAABB();
	CreateEffect();
	for (auto& shot : m_pShots)
	{
		float damage = shot->GetDamage() * (Actor()->GetSkillController()->GetSkill(SKILL_KEY_3)->GetDamage() * 0.01f);
		shot->SetDamage(damage);
	}

	MyUtilities::ANIM_DATA_ARRAY anims(
		{
			{0.0f,0.0f},
			{0.8f,0.0f},
			{0.8f,TimeScaleControllerInstance.GetTimeScale()},
		}
	);
	TimeScaleControllerInstance.SetOtherTimeScale(Actor()->GetType(), anims);


	MyUtilities::ANIM_V3_DATA_ARRAY animPos(
		{
			{0.0f,Vector3(-7,2,-2)},
			{0.25f,Vector3(-7,2,-2),MyUtilities::EASING_TYPE::OUT_SINE},
			{0.30f,Vector3(-25,2,-2),MyUtilities::EASING_TYPE::OUT_SINE},
		}
	);
	MyUtilities::ANIM_V3_DATA_ARRAY animLookPos(
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
	camera = std::make_shared<FixedCamera>(Actor()->GetPosition(), Actor()->GetPosition(), pos, lookPos);
	camera->SetAnim(animPos, animLookPos);
	CameraControllerInstance.SetCamera(camera, 1, MyUtilities::EASING_TYPE::IN_SINE, 0.3f, MyUtilities::EASING_TYPE::IN_SINE, 0.15f);

}

void ActionGame::ShockWaveSkillState::Execution()
{

	for (auto& shot : m_pShots)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
		if (m_CurrentTime >= m_Parameter.CollideStartFrameTime && !collideStartFlg)
		{
			shot->SetEnableCollider(true);
		}
		if (m_CurrentTime > m_Parameter.CollideEndFrameTime)
		{
			if (shot->IsEnableCollider())
			{
				shot->SetEnableCollider(false);
			}
		}

	}
	if (m_CurrentTime >= m_Parameter.CollideStartFrameTime && !collideStartFlg)
	{
		collideStartFlg = true;
	}


	if (Actor()->GetAnimationState()->IsEndMotion())
	{
		if (Actor()->GetTransform()->GetPositionY() > 0)
		{
			ChangeState(STATE_KEY_FALL);
		}
		else
		{
			ChangeState(STATE_KEY_IDLE);
		}

	}

	AttackBaseState::Execution();
}

void ActionGame::ShockWaveSkillState::InputExecution()
{
	AttackBaseState::InputExecution();
}

void ActionGame::ShockWaveSkillState::End()
{
	m_SkillAction->End();
	AttackBaseState::End();
}

void ActionGame::ShockWaveSkillState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::ShockWaveSkillState::GetKey() const
{
	return STATE_KEY_SHOCKWAVE_SKILL;
}
