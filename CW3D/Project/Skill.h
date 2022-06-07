#pragma once
#include "Common.h"
#include "SkillData.h"
#include	"ReactiveParameter.h"
#include	"ParameterHandle.h"

namespace Sample
{
	class CSkill
	{
	private:

		std::string		m_Key;
		std::string		m_Button;
		char*			m_State;
		char*			m_FlyState;
		bool			m_CanUseFlg;
		bool			m_StartFlg;
		SkillDataPtr	m_SkillData;
		Sample::ParameterHandle< Sample::ReactiveParameter<float> > m_CurrentTime;
		Sample::ParameterHandle< Sample::ReactiveParameter<float> > m_CT;

	public:
		CSkill()
			: m_Key()
			, m_Button()
			, m_State(NULL)
			, m_FlyState(NULL)
			, m_CanUseFlg(false)
			, m_SkillData(std::make_shared<CSkillData>())
		{
		}
		~CSkill()
		{
		}

		void Create(std::string key, std::string button, char* state, char* flyState)
		{
			m_Key = key;
			m_Button = button;
			m_State = state;
			m_FlyState = flyState;
			m_CanUseFlg = true;
			m_StartFlg = false;
			m_CT = m_SkillData->CT;
		}

		void Start()
		{
			m_CurrentTime = m_SkillData->CT;
			m_CanUseFlg = false;
			m_StartFlg = true;
		}

		void Update()
		{
			if (!m_StartFlg)
			{
				return;
			}
			if (m_CurrentTime > 0.0f)
			{
				m_CurrentTime -= CUtilities::GetFrameSecond();
			}
			else
			{
				m_StartFlg = false;
				m_CanUseFlg = true;
			}


		}

		std::string GetKey() const noexcept
		{
			return m_Key;
		}

		std::string GetButton() const noexcept
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
			return m_SkillData->CT;
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
			return m_CT;
		}

		int GetDamage() const noexcept
		{
			return m_SkillData->DamagePercent;
		}

		bool GetCanUseFlg() const noexcept
		{
			return m_CanUseFlg;
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
			m_SkillData->CT = ct;
		}

		void SetDamage(float damage) noexcept
		{
			m_SkillData->DamagePercent = damage;
		}

		void SetCanUseFlg(bool isCanUse) noexcept
		{
			m_CanUseFlg = isCanUse;
		}

		void SetSkillData(SkillDataPtr& skill) noexcept
		{
			m_SkillData = skill;
		}

		void SetSkillData(float damagePercent, float ct) noexcept
		{
			m_SkillData->CT = ct;
			m_SkillData->DamagePercent = damagePercent;
		}


	};

	//ポインタ置き換え
	using SKillPtr = std::shared_ptr<CSkill>;
}