#include "NPCStartPoseAction.h"
#include "ParameterDefine.h"

ActionGame::NPCStartPoseAction::NPCStartPoseAction(Parameter param)
	: Action()
	, m_Parameter(param)
	, m_TempOffsetPos(0,0,0)
	, m_CurrentTime(0.0f)
{
}

void ActionGame::NPCStartPoseAction::Start()
{
	StartAnim();
	
	float rotateY = Transform()->GetRotateY();
	m_TempOffsetPos = Vector3(0, 0, 0);

	m_CurrentTime = 0.0f;

	if (Transform()->IsReverse())
	{
		Velocity()->SetRotateY(rotateY, MOF_ToRadian(90), 0.0f);
		m_TempOffsetPos = m_Parameter.offsetPos;
	}
	else
	{
		Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.0f);
		m_TempOffsetPos = -m_Parameter.offsetPos;
	}
	Transform()->MovePosition(m_TempOffsetPos);
	auto& invincible = ParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
	invincible = m_Parameter.finishTime;

	auto& showHP = ParameterMap()->Get<ActionGame::ReactiveParameter<bool>>(PARAMETER_KEY_SHOWHP);
	showHP = false;
}

void ActionGame::NPCStartPoseAction::Execution()
{

	auto& invincible = ParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
	m_CurrentTime += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
	auto& alpha = ParameterMap()->Get<float>(PARAMETER_KEY_ALPHA);
	alpha = MyUtilities::Timer(0.0f, m_CurrentTime, 1.0f, m_Parameter.finishTime);
}

void ActionGame::NPCStartPoseAction::End()
{
	Transform()->MovePosition(-m_TempOffsetPos);
	auto& invincible = ParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
	auto& showHP = ParameterMap()->Get<ActionGame::ReactiveParameter<bool>>(PARAMETER_KEY_SHOWHP);
	showHP = true;
	invincible = 0.0f;
}

void ActionGame::NPCStartPoseAction::StartAnim()
{
	AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
		m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);
}

const ActionGame::ActionKeyType ActionGame::NPCStartPoseAction::GetKey() const
{
	return STATE_KEY_NPCSTARTPOSE;
}

bool ActionGame::NPCStartPoseAction::IsEndAnim() const noexcept
{
	return m_CurrentTime >= m_Parameter.finishTime;
}
