#pragma once

#include	"SkillData.h"
#include	"TimeScaleController.h"



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
		bool			m_StartFlg;
		SkillDataPtr	m_SkillData;
		
		Sample::ParameterHandle< Sample::ReactiveParameter<bool> >	m_CanUseFlg;
		Sample::ParameterHandle< Sample::ReactiveParameter<float> > m_CT;


	protected:
		void AddTimerAndResetFlg()
		{
			if (m_CT > 0.0f)
			{
				m_CT -= CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
			}
			else
			{
				m_StartFlg = false;
				m_CanUseFlg = true;
			}
		}

		void AddTimer()
		{
			if (m_CT > 0.0f)
			{
				m_CT -= CUtilities::GetFrameSecond() * TimeScaleControllerInstance.GetTimeScale();
			}
		}

		void ResetFlg()
		{
			if (m_CT <= 0.0f)
			{
				m_StartFlg = false;
				m_CanUseFlg = true;
			}
		}

	public:
		CSkill()
			: m_Key()
			, m_Button()
			, m_State(nullptr)
			, m_FlyState(nullptr)
			, m_CanUseFlg(false)
			, m_CT(0.0f)
			, m_StartFlg(false)
			, m_SkillData(std::make_shared<SkillData>())
			
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

		virtual void Reset()
		{
			m_StartFlg = false;
			m_CanUseFlg = true;
			m_CT = 0.0f;
		}

		virtual void Start()
		{
			m_CT = m_SkillData->MaxCT.Get();
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

		
		/**
		* @brief		ゲッター
		 */
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

		float GetMaxCT() const noexcept
		{
			return m_SkillData->MaxCT.Get();
		}

		float GetCT() const noexcept
		{
			return m_CT.Get();
		}

		
		int GetDamage() const noexcept
		{
			return m_SkillData->DamagePercent;
		}

		virtual bool IsCanUse()
		{
			return m_CanUseFlg.Get();
		}


		/**
		* @brief		CT変化通知
		*/
		Sample::IObservable<float>* GetCTSubject()			{ return &(m_CT.Get()); }
		Sample::IObservable<float>* GetMaxCTSubject()		{ return &(m_SkillData->MaxCT.Get()); }
		Sample::IObservable<bool>* GetCanUseSubject()		{ return &(m_CanUseFlg.Get()); }


		/**
		* @brief		セッター
		 */
		void SetKey(const std::string& key) noexcept
		{
			m_Key = key;
			
		}

		void SetState(char* state, char* flyState) noexcept
		{
			m_State = state;
			m_FlyState = flyState;
		}

		void SetButton(const std::string& button) noexcept
		{
			m_Button = button;
		}

		void SetCT(float ct) noexcept
		{
			m_CT = ct;
		}
		void SubCT(float ct) noexcept
		{
			m_CT = max(m_CT.Get() - ct, 0.0f);
		}

		void SetMaxCT(float ct) noexcept
		{
			m_SkillData->MaxCT = ct;
		}

		void SetDamage(float damage) noexcept
		{
			m_SkillData->DamagePercent = damage;
		}

		void SetCanUseFlg(bool isCanUse) noexcept
		{
			m_CanUseFlg = isCanUse;
		}

		virtual void SetSkillData(const SkillDataPtr& skill)
		{
			m_SkillData = skill;
		}

		void SetSkillData(float damagePercent, float ct) noexcept
		{
			m_SkillData->MaxCT = ct;
			m_SkillData->DamagePercent = damagePercent;
		}
		

	};

	//ポインタ置き換え
	using SKillPtr = std::shared_ptr<CSkill>;
	using SkillWeakPtr = std::weak_ptr<CSkill>;
}