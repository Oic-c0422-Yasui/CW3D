#include "EscapeState.h"
#include "ParameterDefine.h"

ActionGame::EscapeState::EscapeState(Parameter param)
	: AttackBaseState()
	, m_Parameter(param)
	, m_ThroughFlg(false)
	, m_EscapeCurrentTime(0.0f)
	, m_EscapeFlg(false)
{
}

void ActionGame::EscapeState::Start()
{
	m_EscapeAction = Actor()->GetAction<EscapeAction>(GetKey());
	AttackBaseState::Start();
	m_ThroughFlg = false;
	m_EscapeFlg = false;
	m_EscapeCurrentTime = 0.0f;
	m_EscapeAction->Start();
	Actor()->SetArmorLevel(m_Parameter.armorLevel);
	

	if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) ||
		Input()->IsPress(INPUT_KEY_HORIZONTAL))
	{
		m_EscapeAction->Move(Input()->GetAxis(INPUT_KEY_HORIZONTAL), -(Input()->GetAxis(INPUT_KEY_VERTICAL)));
	}
	else
	{
		if (Actor()->IsReverse())
		{
			m_EscapeAction->Move(1, -(Input()->GetAxis(INPUT_KEY_VERTICAL)));
		}
		else
		{
			m_EscapeAction->Move(-1, -(Input()->GetAxis(INPUT_KEY_VERTICAL)));
		}
	}
}

void ActionGame::EscapeState::Execution()
{

	if (m_CurrentTime > m_Parameter.ThroughStartTime && !m_ThroughFlg)
	{
		m_EscapeAction->StartThrough();
		m_ThroughFlg = true;
	}

	//ƒWƒƒƒXƒg‰ñ”ðŽžŠÔ
	if (m_CurrentTime >= m_Parameter.EscapeStartTime)
	{

		if (m_EscapeCurrentTime < m_Parameter.EscapeTime)
		{
			auto& isEscape = Actor()->GetParameterMap()->Get<bool>(PARAMETER_KEY_ESCAPE);
			if (!isEscape)
			{
				isEscape = true;
			}
			m_EscapeCurrentTime += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());
			if (m_EscapeCurrentTime >= m_Parameter.EscapeTime)
			{
				isEscape = false;
			}

		}
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
	if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) ||
		Input()->IsPress(INPUT_KEY_HORIZONTAL) ||
		Input()->IsNegativePress(INPUT_KEY_VERTICAL) ||
		Input()->IsPress(INPUT_KEY_VERTICAL))
	{
		if (m_CurrentTime > m_Parameter.ThroughEndTime)
		{
			if (Actor()->GetTransform()->GetPositionY() > 0)
			{
				if (GetKeepKey() == STATE_KEY_RUN)
				{
					ChangeState(STATE_KEY_RUNFALL);
				}
				else
				{
					ChangeState(STATE_KEY_FALL);
				}
			}
			else
			{
				if (GetKeepKey() == STATE_KEY_RUN)
				{
					ChangeState(STATE_KEY_RUN);
				}
				else
				{
					ChangeState(STATE_KEY_MOVE);
				}
			}
		}
	}

	AttackBaseState::Execution();
}

void ActionGame::EscapeState::InputExecution()
{
	AttackBaseState::InputExecution();
}

void ActionGame::EscapeState::End()
{
	AttackBaseState::End();
	m_EscapeAction->End();
	auto& isEscape = Actor()->GetParameterMap()->Get<bool>(PARAMETER_KEY_ESCAPE);
	isEscape = false;
}

void ActionGame::EscapeState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::EscapeState::GetKey() const
{
	return STATE_KEY_ESCAPE;
}
