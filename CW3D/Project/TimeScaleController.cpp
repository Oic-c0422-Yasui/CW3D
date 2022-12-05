#include	"TimeScaleController.h"

void ActionGame::TimeScaleController::Update()
{
	m_TimeScale.Update();
	m_PlayerTimeScale.Update();
	m_EnemyTimeScale.Update();
}

float ActionGame::TimeScaleController::GetTimeScale(CHARACTER_TYPE type) const noexcept
{
	switch (type)
	{
	case CHARA_PLAYER:
	{
		return min(m_PlayerTimeScale.GetScale(), m_TimeScale.GetScale());
	}
	case CHARA_ENEMY:
	{
		return min(m_EnemyTimeScale.GetScale(), m_TimeScale.GetScale());
	}
	case CHARA_OBJECT:
	{
		break;
	}
	default:
		break;
	}
	return m_TimeScale.GetScale();
}
