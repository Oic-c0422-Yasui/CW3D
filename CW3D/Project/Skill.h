#pragma once
#include "Common.h"

namespace Sample
{
	class CSkill
	{
	private:

		std::string	m_Key;
		std::string m_Button;
		char*		m_State;
		char*		m_FlyState;
		float		m_CT;
		float		m_CurrentTime;
		int			m_Damage;
		bool		m_CanUseFlg;
		bool		m_StartFlg;

	public:
		CSkill()
			: m_Key()
			, m_Button()
			, m_State(NULL)
			, m_FlyState(NULL)
			, m_CT(0)
			, m_Damage(0)
			, m_CanUseFlg(false)
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
		}

		void Start()
		{
			m_CurrentTime = 0;
			m_CanUseFlg = false;
			m_StartFlg = true;
		}

		void Update()
		{
			if (!m_StartFlg)
			{
				return;
			}
			if (m_CurrentTime < m_CT)
			{
				m_CurrentTime += CUtilities::GetFrameSecond();
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
			return m_CT;
		}

		float GetTime() const noexcept
		{
			return m_CurrentTime;
		}

		int GetDamage() const noexcept
		{
			return m_Damage;
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
			m_CT = ct;
		}

		void SetDamage(float damage) noexcept
		{
			m_Damage = damage;
		}

		void SetCanUseFlg(bool isCanUse) noexcept
		{
			m_CanUseFlg = isCanUse;
		}


	};

	//ポインタ置き換え
	using SKillPtr = std::shared_ptr<CSkill>;
}