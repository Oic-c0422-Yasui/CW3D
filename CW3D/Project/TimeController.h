#pragma once

#include "Singleton.h"
#include "GameDefine.h"


namespace Sample
{
	class TimeScale
	{
		float scale;

		float GetScale()
	};

	class CTimeController : public Singleton<CTimeController>
	{
		friend class Singleton<CTimeController>;
	private:

		TimeScale m_TimeScale;
		TimeScale m_PlayerTimeScale;
		TimeScale m_EnemyTimeScale;



		CTimeController()
			: Singleton<CTimeController>()
			, m_TimeScale(1.0f)
			, m_PlayerTimeScale(1.0f)
			, m_EnemyTimeScale(1.0f)
		{
		}

	public:

		void Update()
		{

		}

		float GetTimeScale(const int type) const noexcept
		{
			switch (type)
			{
			case CHARA_PLAYER:
			{

				return min(m_PlayerTimeScale, m_TimeScale);
			}
			case CHARA_ENEMY:
			{
				return min(m_EnemyTimeScale, m_TimeScale);
			}
			case CHARA_OBJECT:
			{
				break;
			}
			default:
				break;
			}
			return m_TimeScale;
		}

		float GetTimeScale()const noexcept
		{
			return m_TimeScale;
		}

		float GetPlayerTimeScale()const noexcept
		{
			return m_PlayerTimeScale;
		}

		float GetEnemyTimeScale()const noexcept
		{
			return m_EnemyTimeScale;
		}

		void Reset() noexcept
		{
			m_TimeScale = 1.0f;
			m_EnemyTimeScale = 1.0f;
			m_PlayerTimeScale = 1.0f;
		}

		void SetTimeScale(const float time) noexcept
		{
			m_TimeScale = time;
		}

		void SetPlayerTimeScale(const float time) noexcept
		{
			m_PlayerTimeScale = time;
		}

		void SetEnemyTimeScale(const float time) noexcept
		{
			m_EnemyTimeScale = time;
		}

	};
}
//簡易アクセス用
#define TimeControllerInstance 	Sample::CTimeController::GetInstance()

