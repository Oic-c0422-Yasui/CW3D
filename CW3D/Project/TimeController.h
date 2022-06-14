#pragma once

#include "Singleton.h"

#include "TimeScale.h"


namespace Sample
{

	class CTimeController : public Singleton<CTimeController>
	{
		friend class Singleton<CTimeController>;
	private:

		CTimeScale m_TimeScale;
		CTimeScale m_PlayerTimeScale;
		CTimeScale m_EnemyTimeScale;



		CTimeController()
			: Singleton<CTimeController>()
			, m_TimeScale()
			, m_PlayerTimeScale()
			, m_EnemyTimeScale()
		{
		}

	public:

		void Update()
		{
			m_TimeScale.Update();
			m_PlayerTimeScale.Update();
			m_EnemyTimeScale.Update();
		}

		float GetTimeScale(const int type) const noexcept
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

		float GetTimeScale()const noexcept
		{
			return m_TimeScale.GetScale();
		}

		float GetPlayerTimeScale()const noexcept
		{
			return m_PlayerTimeScale.GetScale();
		}

		float GetEnemyTimeScale()const noexcept
		{
			return m_EnemyTimeScale.GetScale();
		}

		void Reset() noexcept
		{
			m_TimeScale.Reset();
			m_EnemyTimeScale.Reset();
			m_PlayerTimeScale.Reset();
		}

		//scale,changeTime,easeType
		void SetTimeScale(const float scale, const float changeTime, MyUtilities::EASING_TYPE easeType ) noexcept
		{
			m_TimeScale.SetScale(scale,changeTime,easeType);
		}
		//animData,count
		void SetTimeScale(MyUtilities::ANIM_DATA* anim,int count)
		{
			m_TimeScale.SetScale(anim, count);
		}

		/*void SetPlayerTimeScale(const float scale) noexcept
		{
			m_PlayerTimeScale = time;
		}

		void SetEnemyTimeScale(const float scale) noexcept
		{
			m_EnemyTimeScale = time;
		}*/

	};
}
//簡易アクセス用
#define TimeControllerInstance 	Sample::CTimeController::GetInstance()

