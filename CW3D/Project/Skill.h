#pragma once
#include "Common.h"

namespace Sample
{
	class CSkill
	{
	private:

		std::string	m_Key;
		std::string m_Button;
		char*		m_Name;
		float		m_CT;
		int			m_Damage;
		bool		m_CanUseFlg;

	public:
		CSkill()
			: m_Key()
			, m_Button()
			, m_Name(NULL)
			, m_CT(0)
			, m_Damage(0)
			, m_CanUseFlg(false)
		{
		}
		~CSkill()
		{
		}

		void Create(std::string key, std::string button, char* name)
		{
			m_Key = key;
			m_Button = button;
			m_Name = name;
			m_CanUseFlg = true;
		}

		std::string GetKey() const noexcept
		{
			return m_Key;
		}

		std::string GetButton() const noexcept
		{
			return m_Button;
		}

		char* GetName() const noexcept
		{
			return m_Name;
		}

		float GetCT() const noexcept
		{
			return m_CT;
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

		void SetButton(std::string button) noexcept
		{
			m_Button = button;
		}

		void SetName(char* name) noexcept
		{
			m_Name = name;
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