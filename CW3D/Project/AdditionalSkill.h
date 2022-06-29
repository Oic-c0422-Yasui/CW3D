#pragma once
#include	"Skill.h"

namespace Sample
{
	class CAdditionalSkill : public CSkill
	{
	private:
		Sample::ParameterHandle< Sample::ReactiveParameter<float> >	m_AdditionalCurrentTime;

		int		m_AdditionalCount;

		bool	m_AdditionalFlg;

	public:
		CAdditionalSkill()
			: CSkill()
			, m_AdditionalCount(0)
			, m_AdditionalFlg(false)
		{
		}
		~CAdditionalSkill()
		{
		}

		void Start() override
		{
			CSkill::Start();
			m_AdditionalCurrentTime = m_SkillData.AditionalTime.Get();
			m_AdditionalFlg = true;
		}

		void Update() override
		{
			if (!m_StartFlg)
			{
				return;
			}
			if (m_AdditionalCurrentTime > 0.0f)
			{
				m_AdditionalCurrentTime -= CUtilities::GetFrameSecond() * TimeControllerInstance.GetTimeScale();
			}
			else
			{
				m_AdditionalFlg = false;
				CSkill::AddTimer();
			}
		}

		bool IsAdditional() const noexcept
		{
			return m_AdditionalFlg;
		}

		float GetAdditionalTime() const noexcept
		{
			return m_AdditionalCurrentTime.Get();
		}
		Sample::ParameterHandle< Sample::ReactiveParameter<float> >& GettAdditionalTimeParam()
		{
			return m_AdditionalCurrentTime;
		}

		Sample::ParameterHandle< Sample::ReactiveParameter<float> >& GetAdditionalCurrentTimeParam()
		{
			return m_SkillData.AditionalTime;
		}

		int GetAdditionalCount() const noexcept
		{
			return m_AdditionalCount;
		}

		void SetAdditionalTime(float time) noexcept
		{
			m_SkillData.AditionalTime = time;
		}

		void SetAdditionalCount(float count) noexcept
		{
			m_AdditionalCount = count;
		}

		void SetSkillData(float damagePercent, float ct,float addTime,int addCount) noexcept
		{
			m_SkillData.CT = ct;
			m_SkillData.DamagePercent = damagePercent;
			m_SkillData.AditionalTime = addTime;
			m_SkillData.AditionalCount = addCount;
		}


	};

	//ポインタ置き換え
	using AdditionalSKillPtr = std::shared_ptr<CAdditionalSkill>;
}