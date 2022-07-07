#pragma once
#include	"Skill.h"

namespace Sample
{
	class CAdditionalSkill : public CSkill
	{
	private:
		float m_AddStartTime;

	public:
		CAdditionalSkill()
			: CSkill()

		{
		}
		~CAdditionalSkill()
		{
		}

		void Start() override
		{
			if (!m_AddFlg)
			{
				CSkill::Start();
				m_AddStartTime = m_SkillData.AditionalStartTime;
			}
			else
			{
				m_DelayAddFlg = true;
				AddInput();
			}
		}

		void Update() override
		{
			if (!m_StartFlg)
			{
				return;
			}
			if (m_AddStartTime > 0.0f)
			{
				m_AddStartTime -= CUtilities::GetFrameSecond() * TimeControllerInstance.GetTimeScale();
				if (m_AddStartTime <= 0.0f)
				{
					if (!m_AddFlg)
					{
						m_AddFlg = true;
						m_AddCT = m_SkillData.AditionalTime.Get();
						m_DelayAddFlg = false;
					}
				}
			}
			else if (m_AddCT > 0.0f)
			{
				m_AddCT -= CUtilities::GetFrameSecond() * TimeControllerInstance.GetTimeScale();
			}
			
			if(m_AddCT <= 0.0f)
			{
				m_AddFlg = false;
				CSkill::AddTimerAndResetFlg();
			}
		}

		
		void SetAddCT(float time) noexcept
		{
			m_AddCT = time;
		}
		void SetAddMaxCT(float time) noexcept
		{
			m_SkillData.AditionalTime = time;
		}

		void SetAddCount(float count) noexcept
		{
			m_AddCount = count;
		}

		void SetSkillData(float damagePercent, float ct,float addTime,int addCount) noexcept
		{
			m_SkillData.CT = ct;
			m_SkillData.DamagePercent = damagePercent;
			m_SkillData.AditionalTime = addTime;
			m_SkillData.AditionalCount = addCount;
		}

		void AddInput() override
		{
			SetAddCT(0.0f);
			m_AddFlg = false;
		}

		bool IsCanUse() override
		{
			return m_AddFlg | m_CanUseFlg.Get();
		}

	};

	//ポインタ置き換え
	using AdditionalSKillPtr = std::shared_ptr<CAdditionalSkill>;
	using AdditionalWeakSKillPtr = std::weak_ptr<CAdditionalSkill>;
}