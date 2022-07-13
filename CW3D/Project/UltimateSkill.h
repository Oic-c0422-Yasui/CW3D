#pragma once
#include	"Skill.h"
#include	"IActor.h"

namespace Sample
{
	class CUltimateSkill : public CSkill
	{
	private:

		bool m_MaxGaugeFlg;

		ActorWeakPtr m_Actor;
		UltimateSkillDataPtr m_UltSkillData;
	public:
		CUltimateSkill(const ActorWeakPtr& actor)
			: CSkill()
			, m_Actor(actor)
			,m_MaxGaugeFlg(false)
		{
		}
		~CUltimateSkill()
		{
		}
		void Create(const std::string& key, const std::string& button, const std::string& texName, char* state, char* flyState) override
		{
			CSkill::Create(key, button,texName, state, flyState);
			m_CanUseFlg = false;
		}

		void Start() override
		{
			CSkill::Start();
			auto& currentGauge = m_Actor.lock()->GetParameterMap()->Get<ReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
			currentGauge -= m_UltSkillData->ExpendGauge.Get();
		}

		void Reset() override
		{
			CSkill::Reset();
			m_CanUseFlg = false;
			m_MaxGaugeFlg = false;
		}

		void Update() override
		{
			if (!m_CanUseFlg.Get() && !m_StartFlg)
			{
				auto& currentGauge = m_Actor.lock()->GetParameterMap()->Get<ReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
				if (currentGauge >= m_UltSkillData->ExpendGauge.Get() && m_CT <= 0.0f)
				{
					m_CanUseFlg = true;
				}
			}
			if (!m_StartFlg)
			{
				return;
			}
			CSkill::AddTimer();
			auto& currentGauge = m_Actor.lock()->GetParameterMap()->Get<ReactiveParameter<float>>(PARAMETER_KEY_ULTGAUGE);
			if (currentGauge >= m_UltSkillData->ExpendGauge.Get() && m_CT <= 0.0f)
			{
				CSkill::ResetFlg();
			}
		}


		float GetExpendGauge() const noexcept
		{
			return m_UltSkillData->ExpendGauge.Get();
		}
		Sample::ParameterHandle< Sample::ReactiveParameter<float> >& GettExpendGaugeParam()
		{
			return m_UltSkillData->ExpendGauge;
		}

		void SetSkillData(const SkillDataPtr& skill) override
		{
			CSkill::SetSkillData(skill);
			m_UltSkillData = std::dynamic_pointer_cast<UltimateSkillData>(m_SkillData);
			if (m_UltSkillData == nullptr)
			{
				assert(m_UltSkillData);
			}
		}

		//•KE‹ZƒQ[ƒW
		float GetUltGauge() const noexcept
		{
			return m_UltSkillData->ExpendGauge.Get();
		}
		//•KE‹ZƒQ[ƒW’Ê’m
		Sample::IObservable<float>* GetSkillUltSubject(int id) { return &(m_UltSkillData->ExpendGauge.Get()); }
	};

	//ƒ|ƒCƒ“ƒ^’u‚«Š·‚¦
	using UltimateSkillPtr = std::shared_ptr<CUltimateSkill>;
	using UltimateWeakSkillPtr = std::weak_ptr<CUltimateSkill>;
}