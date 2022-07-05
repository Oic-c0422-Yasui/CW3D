#pragma once

#include	"SkillData.h"
#include	"TimeController.h"


namespace Sample
{
	class CSkill
	{
	public:
	protected:
		std::string		m_Key;
		std::string		m_TexName;
		std::string		m_Button;
		char*			m_State;
		char*			m_FlyState;
		Sample::ParameterHandle< Sample::ReactiveParameter<bool> >			m_CanUseFlg;
		bool			m_StartFlg;
		CSkillData	m_SkillData;
		
		Sample::ParameterHandle< Sample::ReactiveParameter<float> > m_CurrentTime;

		void AddTimerAndResetFlg()
		{
			if (m_CurrentTime > 0.0f)
			{
				m_CurrentTime -= CUtilities::GetFrameSecond() * TimeControllerInstance.GetTimeScale();
			}
			else
			{
				m_StartFlg = false;
				m_CanUseFlg = true;
			}
		}

		void AddTimer()
		{
			if (m_CurrentTime > 0.0f)
			{
				m_CurrentTime -= CUtilities::GetFrameSecond() * TimeControllerInstance.GetTimeScale();
			}
		}

		void ResetFlg()
		{
			if (m_CurrentTime <= 0.0f)
			{
				m_StartFlg = false;
				m_CanUseFlg = true;
			}
		}

	public:
		CSkill()
			: m_Key()
			, m_Button()
			, m_State(NULL)
			, m_FlyState(NULL)
			, m_CanUseFlg(false)
			, m_SkillData()
			, m_StartFlg(false)
		{
		}

		virtual ~CSkill()
		{
		}

		virtual void Create(const std::string& key, const std::string& button, const std::string& texName, char* state, char* flyState)
		{
			m_Key = key;
			m_Button = button;
			m_TexName = texName;
			m_State = state;
			m_FlyState = flyState;
			m_CanUseFlg = true;
			m_StartFlg = false;
		}

		virtual void Start()
		{
			m_CurrentTime = m_SkillData.CT.Get();
			m_CanUseFlg = false;
			m_StartFlg = true;
		}

		virtual void Update()
		{
			if (!m_StartFlg)
			{
				return;
			}
			AddTimerAndResetFlg();
		}

		

		const std::string& GetKey() const noexcept
		{
			return m_Key;
		}

		const std::string& GetTexName() const noexcept
		{
			return m_TexName;
		}

		const std::string& GetButton() const noexcept
		{
			return m_Button;
		}

		char* GetState() const noexcept
		{
			return m_State;
		}

		char* GetFlyState() const noexcept
		{
			return m_FlyState;
		}

		float GetCT() const noexcept
		{
			return m_SkillData.CT.Get();
		}

		float GetTime() const noexcept
		{
			return m_CurrentTime.Get();
		}

		Sample::ParameterHandle< Sample::ReactiveParameter<float> >& GetTimeParam()
		{
			return m_CurrentTime;
		}

		Sample::ParameterHandle< Sample::ReactiveParameter<float> >& GetCTParam()
		{
			return m_SkillData.CT;
		}
		Sample::ParameterHandle< Sample::ReactiveParameter<int> >& GetDamageParam()
		{
			return m_SkillData.DamagePercent;
		}

		Sample::ParameterHandle< Sample::ReactiveParameter<float> >& GetUltGaugeParam()
		{
			return m_SkillData.ExpendGauge;
		}

		Sample::ParameterHandle< Sample::ReactiveParameter<bool> >& GetCanUseFlgParam()
		{
			return m_CanUseFlg;
		}

		int GetDamage() const noexcept
		{
			return m_SkillData.DamagePercent.Get();
		}

		float GetUltGauge() const noexcept
		{
			return m_SkillData.ExpendGauge.Get();
		}

		bool GetCanUseFlg() const noexcept
		{
			return m_CanUseFlg.Get();
		}

		void SetKey(std::string key) noexcept
		{
			m_Key = key;
			
		}

		void SetState(char* state, char* flyState) noexcept
		{
			m_State = state;
			m_FlyState = flyState;
		}

		void SetButton(std::string button) noexcept
		{
			m_Button = button;
		}

		void SetCT(float ct) noexcept
		{
			m_SkillData.CT = ct;
		}

		void SetDamage(float damage) noexcept
		{
			m_SkillData.DamagePercent = damage;
		}

		void SetCanUseFlg(bool isCanUse) noexcept
		{
			m_CanUseFlg = isCanUse;
		}

		void SetSkillData(const CSkillData& skill) noexcept
		{
			m_SkillData = skill;
		}

		void SetSkillData(float damagePercent, float ct) noexcept
		{
			m_SkillData.CT = ct;
			m_SkillData.DamagePercent = damagePercent;
		}


	};

	//ポインタ置き換え
	using SKillPtr = std::shared_ptr<CSkill>;
}