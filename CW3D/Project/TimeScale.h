#pragma once
#include "GameDefine.h"


namespace Sample
{
#define ARRAY_LENGTH(m_AnimData) (sizeof(m_AnimData) / sizeof(m_AnimData[0]))
	class CTimeScale
	{
	private:
		float	m_Time;
		MyUtilities::ANIM_DATA m_AnimData[10];
		float	m_ChangeTime;
		bool	m_ChangeFlg;
		float	m_CurrentTime;
		int		m_Count;

	public:
		CTimeScale()
			: m_Time(1.0f)
			, m_ChangeFlg(false)
			, m_ChangeTime(0.0f)
			, m_Count(0)
			, m_AnimData()
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
			m_Count = 2;
			MyUtilities::ANIM_DATA anim[2] =
			{
				{0, m_Time, easeType},
				{changeTime, scale, easeType}
			};
			m_AnimData[0] = anim[0];
			m_AnimData[1] = anim[1];
			m_CurrentTime = 0.0f;
			m_ChangeTime = changeTime;
			m_ChangeFlg = true;
		}

		void SetScale(MyUtilities::ANIM_DATA* anim,int count)
		{
			memcpy(m_AnimData, anim, sizeof(MyUtilities::ANIM_DATA) * count);
			m_Count = count;
			m_ChangeTime = m_AnimData[count - 1].Time;
			m_CurrentTime = 0.0f;
			m_ChangeFlg = true;
		}

		void Reset() noexcept
		{
			m_Time = 1.0f;
			m_CurrentTime = 0.0f;
			m_ChangeTime = 0.0f;
			m_ChangeFlg = false;
		}

	};
}