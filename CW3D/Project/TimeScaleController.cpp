#include	"TimeScaleController.h"

void ActionGame::TimeScaleController::Update()
{
	m_TimeScale.Update();
	m_PlayerTimeScale.Update();
	m_EnemyTimeScale.Update();
}

float ActionGame::TimeScaleController::GetTimeScale(CHARA_TYPE type) const noexcept
{
	switch (type)
	{
	case CHARA_TYPE::PLAYER:
	{
		return min(m_PlayerTimeScale.GetScale(), m_TimeScale.GetScale());
	}
	case CHARA_TYPE::ENEMY:
	{
		return min(m_EnemyTimeScale.GetScale(), m_TimeScale.GetScale());
	}
	case CHARA_TYPE::OBJECT:
	{
		break;
	}
	default:
		break;
	}
	return m_TimeScale.GetScale();
}
