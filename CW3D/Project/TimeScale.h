#pragma once
#include "GameDefine.h"


namespace Sample
{
#define ARRAY_LENGTH(m_AnimData) (sizeof(m_AnimData) / sizeof(m_AnimData[0]))
	class CTimeScale
	{
	private:
		float	m_Time;
		MyUtilities::ANIM_DATA* m_AnimData;
		float	m_ChangeTime;
		bool	m_ChangeFlg;
		float	m_CurrentTime;
		int		m_Count;

	public:
		CTimeScale()
			: m_Time(1.0f)
			, m_ChangeFlg(false)
			, m_ChangeTime(0.0f)
			, m_AnimData()
			, m_Count(0)
		{
		}
		~CTimeScale() {
		}

		void Update()
		{
			if (!m_ChangeFlg)
			{
				return;
			}
			if (m_ChangeTime > m_CurrentTime)
			{
				m_CurrentTime += CUtilities::GetFrameSecond();
				
			}
			else
			{
				m_ChangeFlg = false;
			}
			m_Time = MyUtilities::InterpolationAnim(m_CurrentTime, m_AnimData, m_Count);
		}

		float GetScale() const noexcept
		{
			return m_Time;
		}

		void SetScale(const float scale, const float changeTime, MyUtilities::EASING_TYPE easeType) noexcept
		{
			MyUtilities::ANIM_DATA anim[] =
			{
				{changeTime,scale,easeType},
			};
			m_Count = _countof(anim);
			m_AnimData = anim;
			m_CurrentTime = 0.0f;
			m_ChangeFlg = true;
		}

		void SetScale(MyUtilities::ANIM_DATA* anim,int count)
		{
			m_AnimData = anim;
			m_Count = count;
			m_CurrentTime = 0.0f;
			m_ChangeFlg = true;
		}

		void Reset() noexcept
		{
			m_Time = 1.0f;
			m_CurrentTime = 0.0f;
			m_ChangeFlg = false;
		}

	};
}