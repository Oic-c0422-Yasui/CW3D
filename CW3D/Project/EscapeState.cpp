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

	auto& armorLevel = Actor()->GetParameterMap()->Get<BYTE>(PARAMETER_KEY_ARMORLEVEL);
	armorLevel = m_Parameter.armorLevel;

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

	//ジャスト回避時間
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

	

	AttackBaseState::Execution();
}

void ActionGame::EscapeState::InputExecution()
{
	float scale = TimeScaleControllerInstance.GetTimeScale(Actor()->GetType());
	//タイムスケールが0以下の場合、入力を受け付けない
	if (scale <= 0.0f)
	{
		return;
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
					ChangeState(STATE_KEY_RUN_FALL);
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
