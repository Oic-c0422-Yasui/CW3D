#pragma once
#include	"Skill.h"
#include	"IActor.h"

namespace Sample
{
	class CUltimateSkill : public CSkill
	{
	private:

		bool m_MaxGaugeFlg;

		ActorPtr m_Actor;

	public:
		CUltimateSkill()
			: CSkill()
		{
		}
		~CUltimateSkill()
		{
		}
		void Create(std::string key, std::string button, char* state, char* flyState) override
		{
			CSkill::Create(key, button, state, flyState);
			m_CanUseFlg = false;
		}

		void Start() override
		{
			CSkill::Start();
			auto& currentGauge = m_Actor->GetParameterMap()->Get<ReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
			currentGauge -= m_SkillData.ExpendGauge.Get();
		}

		void Update() override
		{
			if (!m_CanUseFlg && !m_StartFlg)
			{
				auto& currentGauge = m_Actor->GetParameterMap()->Get<ReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
				if (currentGauge >= m_SkillData.ExpendGauge.Get() && m_CurrentTime <= 0.0f)
				{
					m_CanUseFlg = true;
				}
			}
			if (!m_StartFlg)
			{
				return;
			}
			CSkill::AddTimer();
			auto& currentGauge = m_Actor->GetParameterMap()->Get<ReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
			if (currentGauge >= m_SkillData.ExpendGauge.Get() && m_CurrentTime <= 0.0f)
			{
				CSkill::ResetFlg();
			}
		}


		float GetExpendGauge() const noexcept
		{
			return m_SkillData.ExpendGauge.Get();
		}
		Sample::ParameterHandle< Sample::ReactiveParameter<float> >& GettExpendGaugeParam()
		{
			return m_SkillData.ExpendGauge;
		}

		void SetAdditionalTime(float time) noexcept
		{
			m_SkillData.AditionalTime = time;
		}

		void SetSkillData(float damagePercent, float ct, float ) noexcept
		{
			m_SkillData.CT = ct;
			m_SkillData.DamagePercent = damagePercent;
		}
		void SetActor(const ActorPtr& actor)
		{
			m_Actor = actor;
		}
	};

	//ポインタ置き換え
	using UltimateSKillPtr = std::shared_ptr<CUltimateSkill>;
	using UltimateWeakSKillPtr = std::weak_ptr<CUltimateSkill>;
}