#pragma once
#include	"Skill.h"

namespace Sample
{
	class CAdditionalSkill : public CSkill
	{
	private:
		float m_AddStartTime;
		Sample::ParameterHandle< Sample::ReactiveParameter<float> >	m_AddCT;
		int		m_AddCount;
		bool	m_AddFlg;
		bool	m_DelayAddFlg;
		AdditionalSkillDataPtr m_AddSkillData;
	public:
		CAdditionalSkill()
			: CSkill()
			, m_AddStartTime(0.0f)
			, m_AddCT(0.0f)
			, m_AddCount(0)
			, m_AddFlg(false)
			, m_DelayAddFlg(false)
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
				m_AddStartTime = m_AddSkillData->StartTime;
			}
			else
			{
				m_DelayAddFlg = true;
				AddInput();
			}
		}

		void Reset() override
		{
			CSkill::Reset();
			m_AddStartTime = 0.0f;
			m_AddCT = 0.0f;
			m_AddCount = 0;
			m_AddFlg = false;
			m_DelayAddFlg = false;
		}

		void Update() override
		{
			if (!m_StartFlg)
			{
				return;
			}
			if (m_AddStartTime > 0.0f)
			{
				m_AddStartTime -= CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
				if (m_AddStartTime <= 0.0f)
				{
					if (!m_AddFlg)
					{
						m_AddFlg = true;
						m_AddCT = m_AddSkillData->AddMaxCT.Get();
						m_DelayAddFlg = false;
					}
				}
			}
			else if (m_AddCT > 0.0f)
			{
				m_AddCT -= CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
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
			m_AddSkillData->AddMaxCT = time;
		}

		void SetAddCount(float count) noexcept
		{
			m_AddCount = count;
		}

		void AddInput()
		{
			SetAddCT(0.0f);
			m_AddFlg = false;
		}

		bool IsAdditional() const noexcept
		{
			return m_AddFlg;
		}
		virtual bool IsDelayAdditional()
		{
			return m_DelayAddFlg;
		}

		float GetAddCT() const noexcept
		{
			return m_AddCT.Get();
		}
		float GetAddMaxCT() const noexcept
		{
			return m_AddSkillData->AddMaxCT.Get();
		}


		int GetAddCount() const noexcept
		{
			return m_AddCount;
		}

		bool IsCanUse() override
		{
			return m_AddFlg | m_CanUseFlg.Get();
		}


		void SetSkillData(const SkillDataPtr& skill) override
		{
			CSkill::SetSkillData(skill);
			m_AddSkillData = std::dynamic_pointer_cast<AdditionalSkillData>(m_SkillData);
			if (m_AddSkillData == nullptr)
			{
				assert(m_AddSkillData);
			}
		}

		Sample::IObservable<float>* GetAddCTSubject() { return &(m_AddCT.Get()); }
		Sample::IObservable<float>* GetAddMaxCTSubject() { return &(m_AddSkillData->MaxCT.Get()); }

	};

	//ポインタ置き換え
	using AdditionalSKillPtr = std::shared_ptr<CAdditionalSkill>;
	using AdditionalWeakSKillPtr = std::weak_ptr<CAdditionalSkill>;
}