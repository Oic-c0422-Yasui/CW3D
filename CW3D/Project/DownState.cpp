#include "DownState.h"

ActionGame::DownState::DownState(Parameter param)
	: State()
	, m_Parameter(param)
	, m_CurrentTime(0) {
}

void ActionGame::DownState::Start()
{
	m_CurrentTime = 0;
	auto& invincible = Actor()->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
	invincible = m_Parameter.endTime;
	m_DownAction = Actor()->GetAction<DownAction>(GetKey());
	m_DownAction->Start();
}

void ActionGame::DownState::Execution()
{
	m_DownAction->Execution();

	if (m_CurrentTime < m_Parameter.endTime)
	{
		m_CurrentTime += CUtilities::GetFrameSecond();
	}
	else
	{
		ChangeState(STATE_KEY_IDLE);
	}
}

void ActionGame::DownState::InputExecution()
{
}

void ActionGame::DownState::End()
{
	m_DownAction->End();
}

void ActionGame::DownState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::DownState::GetKey() const
{
	return STATE_KEY_DOWN;
}
