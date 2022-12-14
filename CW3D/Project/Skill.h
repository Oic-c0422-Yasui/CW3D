#pragma once

#include	"SkillData.h"
#include	"TimeScaleController.h"



namespace ActionGame
{
	
	class Skill
	{
	public:
	protected:
		std::string		m_Key;
		std::string		m_TexName;
		std::string		m_InputKey;
		char*			m_State;
		char*			m_FlyState;
		bool			m_StartFlg;
		SkillDataPtr	m_SkillData;
		
		ActionGame::ParameterHandle< ActionGame::ReactiveParameter<bool> >	m_CanUseFlg;
		ActionGame::ParameterHandle< ActionGame::ReactiveParameter<float> > m_CT;


	protected:
		/*		プライベート関数		*/
		
		//時間を進める
		void AddTimer();

		//リセット判定
		void ResetFlg();

		//時間を進める＆リセット判定
		void AddTimerAndResetFlg();

	public:
		Skill();

		virtual ~Skill() = default;
		
		/*
		* @brief	スキル生成
		* @param	name スキル名
		* @param	inputKey インプットキー名
		* @param	texName	スキルテクスチャの名前
		* @param	state	ステート名
		* @param	state	空中ステート名
		*/
		virtual void Create(const std::string& name, const std::string& inputKey, const std::string& texName, char* state, char* flyState);

		/*
		* @brief	開始
		*/
		virtual void Start();

		/*
		* @brief	リセット
		*/
		virtual void Reset();

		/*
		* @brief	更新
		*/
		virtual void Update();



		/////////////////////////////////////////////////////////////////////
		///			ゲッター
		////////////////////////////////////////////////////////////////////
		
		/**
		* @brief		スキル名を取得
		*/
		const std::string& GetKey() const noexcept
		{
			return m_Key;
		}

		/*
		* @brief		テクスチャ名を取得
		*/
		const std::string& GetTexName() const noexcept
		{
			return m_TexName;
		}

		/*
		* @brief		インプットキー名を取得
		*/
		const std::string& GetButton() const noexcept
		{
			return m_InputKey;
		}

		/*
		* @brief		ステート名を取得
		*/
		char* GetState() const noexcept
		{
			return m_State;
		}

		/*
		* @brief		空中ステート名を取得
		*/
		char* GetFlyState() const noexcept
		{
			return m_FlyState;
		}

		/*
		* @brief		最大クールタイムを取得
		*/
		float GetMaxCT() const noexcept
		{
			return m_SkillData->MaxCT.Get();
		}

		/*
		* @brief		現在のクールタイムを取得
		*/
		float GetCT() const noexcept
		{
			return m_CT.Get();
		}

		/*
		* @brief		スキルのダメージ量を取得
		* @return		スキルのダメージ量(%)
		*/
		int GetDamage() const noexcept
		{
			return m_SkillData->DamagePercent;
		}

		/*
		* @brief	スキルが使用できるか？
		* @param	true　なら使用可能
		*/
		virtual bool IsCanUse()
		{
			return m_CanUseFlg.Get();
		}


		/**
		* @brief		CT変化通知
		*/
		ActionGame::IObservable<float>* GetCTSubject()			{ return &(m_CT.Get()); }
		ActionGame::IObservable<float>* GetMaxCTSubject()		{ return &(m_SkillData->MaxCT.Get()); }
		ActionGame::IObservable<bool>* GetCanUseSubject()		{ return &(m_CanUseFlg.Get()); }


		/////////////////////////////////////////////////////////////////////
		///			セッター
		////////////////////////////////////////////////////////////////////

		/**
		* @brief		スキル名を設定
		*/
		void SetKey(const std::string& key) noexcept
		{
			m_Key = key;
			
		}

		/*
		* @brief		ステート名を取得
		* @param		state		ステート名
		* @param		flyState	空中ステート名
		*/
		void SetState(char* state, char* flyState) noexcept
		{
			m_State = state;
			m_FlyState = flyState;
		}

		/*
		* @brief		インプットキー名を取得
		*/
		void SetButton(const std::string& button) noexcept
		{
			m_InputKey = button;
		}

		/*
		* @brief		現在のクールタイムを取得
		* @param		クールタイム(秒)
		*/
		void SetCT(float ct) noexcept
		{
			m_CT = ct;
		}
		/*
		* @brief		現在のクールタイムを減少
		* @param		減少させるクールタイム(秒)
		*/
		void SubCT(float ct) noexcept
		{
			m_CT = max(m_CT.Get() - ct, 0.0f);
		}

		/*
		* @brief		最大のクールタイムを設定
		* @param		最大クールタイム(秒)
		*/
		void SetMaxCT(float ct) noexcept
		{
			m_SkillData->MaxCT = ct;
		}

		/*
		* @brief		スキルのダメージ量を設定
		* @param		damage スキルのダメージ量(%)
		*/
		void SetDamage(float damage) noexcept
		{
			m_SkillData->DamagePercent = damage;
		}

		/*
		* @brief		使用可能可否を設定
		* @param		true　なら使用可能
		*/
		void SetCanUseFlg(bool isCanUse) noexcept
		{
			m_CanUseFlg = isCanUse;
		}

		/*
		* @brief		スキルデータを設定
		* @param		skill スキルデータ
		*/
		virtual void SetSkillData(const SkillDataPtr& skill)
		{
			m_SkillData = skill;
		}

		/*
		* @brief		スキルデータを設定
		* @param		damage ダメージ量(%)
		* @param		ct	最大クールタイム(秒)
		*/
		void SetSkillData(float damage, float ct) noexcept
		{
			m_SkillData->MaxCT = ct;
			m_SkillData->DamagePercent = damage;
		}
		

	};

	//ポインタ置き換え
	using SKillPtr = std::shared_ptr<Skill>;
	using SkillWeakPtr = std::weak_ptr<Skill>;
}