#include "StormSkillState.h"
#include "FollowFixedCamera.h"
#include "CameraController.h"

ActionGame::StormSkillState::StormSkillState(Parameter param)
	: AttackBaseState()
	, m_Parameter(param)
	, m_ContinueFlg(false)
	, m_AttackTime(0.0f)
{
}

void ActionGame::StormSkillState::Start()
{
	m_SkillAction = Actor()->GetAction<StormSkillAction>(GetKey());

	m_AttackTime = 0.0f;

	m_ContinueFlg = true;


	AttackBaseState::Start();
	m_SkillAction->Start();
	CreateShotAABB();
	CreateEffect();
	for (auto& shot : m_pShots)
	{
		int damage = (int)(shot->GetDamage() * (Actor()->GetSkillController()->GetSkill(SKILL_KEY_2)->GetDamage() * 0.01f));
		shot->SetDamage(damage);
	}


	m_Key = Actor()->GetSkillController()->GetSkill(SKILL_KEY_2)->GetButton();

	Vector3 pos(0, 10, -20);
	Vector3 lookPos(0, 3, 0);
	if (Actor()->IsReverse())
	{
		pos.x *= -1;
		lookPos.x *= -1;
	}
	CameraPtr camera;
	camera = std::make_shared<ActionGame::FollowFixedCamera>(Actor()->GetPosition(), Actor()->GetPosition(), pos, lookPos);
	CameraControllerInstance.SetCamera(camera, 2.3f, MyUtilities::EASE_IN_SINE, 0.7f, MyUtilities::EASE_IN_SINE, 0.5f);
}

void ActionGame::StormSkillState::Execution()
{

	for (auto& shot : m_pShots)
	{
		shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
		if (m_AttackTime >= m_Parameter.AttackFrequencyFrameTime)
		{
			shot->SetCollideFlg(true);

		}
		else if (shot->GetCollideFlg())
		{
			shot->SetCollideFlg(false);
		}

	}
	if (m_AttackTime >= m_Parameter.AttackFrequencyFrameTime)
	{
		m_AttackTime = 0.0f;
	}


	for (auto& effect : m_pEffects)
	{
		EffectControllerInstance.SetPosition(effect->GetHandle(), Actor()->GetPosition() + m_Parameter.EffectStatus.offset);
	}

	m_AttackTime += CUtilities::GetFrameSecond();

	if (m_CurrentTime > m_Parameter.DurationTime || !m_ContinueFlg)
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

void ActionGame::StormSkillState::InputExecution()
{
	if (m_CurrentTime > 0.5f)
	{
		if (Input()->IsPress(m_Key))
		{
			m_ContinueFlg = true;
		}
		else
		{
			m_ContinueFlg = false;
		}
	}

	if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) ||
		Input()->IsPress(INPUT_KEY_HORIZONTAL) ||
		Input()->IsNegativePress(INPUT_KEY_VERTICAL) ||
		Input()->IsPress(INPUT_KEY_VERTICAL))
	{
		m_SkillAction->Acceleration(Input()->GetAxis(INPUT_KEY_HORIZONTAL), -(Input()->GetAxis(INPUT_KEY_VERTICAL)));
	}

	AttackBaseState::InputExecution();
}

void ActionGame::StormSkillState::End()
{
	m_SkillAction->End();
	AttackBaseState::End();
	CameraControllerInstance.SetDefault();

}

void ActionGame::StormSkillState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::StormSkillState::GetKey() const
{
	return STATE_KEY_STORMSKILL;
}

