#include "NPCStartPoseState.h"

ActionGame::NPCStartPoseState::NPCStartPoseState(Parameter param)
	: State()
	, m_CurrentTime(0)
	, m_Parameter(param)
{
}

void ActionGame::NPCStartPoseState::Start()
{
	m_CurrentTime = 0.0f;
	m_Action = Actor()->GetAction<NPCStartPoseAction>(GetKey());
	m_Action->Start();
	
}

void ActionGame::NPCStartPoseState::Execution()
{
	if (m_Parameter.Time > m_CurrentTime)
	{
		m_Action->Execution();
		m_CurrentTime += CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
	}
	else
	{
		ChangeState(STATE_KEY_IDLE);
	}
}

void ActionGame::NPCStartPoseState::InputExecution()
{
}

void ActionGame::NPCStartPoseState::End()
{
	m_Action->End();
}

void ActionGame::NPCStartPoseState::CollisionEvent(unsigned int type, std::any obj)
{
}

const ActionGame::StateKeyType ActionGame::NPCStartPoseState::GetKey() const
{
	return STATE_KEY_NPCSTARTPOSE;
}
