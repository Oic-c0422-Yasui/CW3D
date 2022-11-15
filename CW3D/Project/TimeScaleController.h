#pragma once

#include "Singleton.h"

#include "TimeScale.h"


namespace Sample
{

	class CTimeScaleController : public Singleton<CTimeScaleController>
	{
		friend class Singleton<CTimeScaleController>;
	private:

		CTimeScale m_TimeScale;
		CTimeScale m_PlayerTimeScale;
		CTimeScale m_EnemyTimeScale;

		CTimeScaleController()
			: Singleton<CTimeScaleController>()
			, m_TimeScale()
			, m_PlayerTimeScale()
			, m_EnemyTimeScale()
		{
		}

	public:
		~CTimeScaleController() {}


		void Update()
		{
			m_TimeScale.Update();
			m_PlayerTimeScale.Update();
			m_EnemyTimeScale.Update();
		}


		float GetTimeScale(CHARACTER_TYPE type) const noexcept
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

		void SetTimeScale(CHARACTER_TYPE id,const float scale, const float changeTime, MyUtilities::EASING_TYPE easeType) noexcept
		{
			switch (id)
			{
			case CHARA_PLAYER:
			{
				m_PlayerTimeScale.SetScale(scale, changeTime, easeType);
				break;
			}
			case CHARA_ENEMY:
			{
				m_EnemyTimeScale.SetScale(scale, changeTime, easeType);
				break;
			}
			default:
				break;
			}
			
		}
		//animData,count
		void SetTimeScale(CHARACTER_TYPE id, MyUtilities::ANIM_DATA* anim, int count)
		{
			switch (id)
			{
			case CHARA_PLAYER:
			{
				m_PlayerTimeScale.SetScale(anim,count);
				break;
			}
			case CHARA_ENEMY:
			{
				m_EnemyTimeScale.SetScale(anim, count);
				break;
			}
			default:
				break;
			}
		}


		//ID以外のタイムスケールを変える
		void SetOtherTimeScale(CHARACTER_TYPE id, const float scale, const float changeTime, MyUtilities::EASING_TYPE easeType) noexcept
		{
			switch (id)
			{
			case CHARA_PLAYER:
			{
				m_EnemyTimeScale.SetScale(scale, changeTime, easeType);
				
				break;
			}
			case CHARA_ENEMY:
			{
				m_PlayerTimeScale.SetScale(scale, changeTime, easeType);
				break;
			}
			default:
				break;
			}

		}
		//animData,count
		void SetOtherTimeScale(CHARACTER_TYPE id, MyUtilities::ANIM_DATA* anim, int count)
		{
			switch (id)
			{
			case CHARA_PLAYER:
			{
				m_EnemyTimeScale.SetScale(anim, count);
				break;
			}
			case CHARA_ENEMY:
			{
				m_PlayerTimeScale.SetScale(anim, count);
				break;
			}
			default:
				break;
			}
		}

	};
}
//簡易アクセス用
#define TimeScaleControllerInstance 	Sample::CTimeScaleController::GetInstance()

