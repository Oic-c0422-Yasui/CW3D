#pragma once

#include	"SkillData.h"
#include	"TimeScaleController.h"



namespace ActionGame
{
	
	class CSkill
	{
	public:
	protected:
		std::string		skillName_;
		std::string		texureName_;
		std::string		inputKey_;
		char*			stateName_;
		char*			flyStateName_;
		bool			isStart_;
		SkillDataPtr	skillData_;
		
		ActionGame::ParameterHandle< ActionGame::CReactiveParameter<bool> >	canUse_;
		ActionGame::ParameterHandle< ActionGame::CReactiveParameter<float> > CT_;


	protected:
		/*		プライベート関数		*/
		
		//時間を進める
		void AddTimer();

		//リセット判定
		void ResetFlg();

		//時間を進める＆リセット判定
		void AddTimerAndResetFlg();

	public:
		CSkill();

		virtual ~CSkill() = default;
		
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
			return skillName_;
		}

		/*
		* @brief		テクスチャ名を取得
		*/
		const std::string& GetTexName() const noexcept
		{
			return texureName_;
		}

		/*
		* @brief		インプットキー名を取得
		*/
		const std::string& GetButton() const noexcept
		{
			return inputKey_;
		}

		/*
		* @brief		ステート名を取得
		*/
		char* GetState() const noexcept
		{
			return stateName_;
		}

		/*
		* @brief		空中ステート名を取得
		*/
		char* GetFlyState() const noexcept
		{
			return flyStateName_;
		}

		/*
		* @brief		最大クールタイムを取得
		*/
		float GetMaxCT() const noexcept
		{
			return skillData_->MaxCT.Get();
		}

		/*
		* @brief		現在のクールタイムを取得
		*/
		float GetCT() const noexcept
		{
			return CT_.Get();
		}

		/*
		* @brief		スキルのダメージ量を取得
		* @return		スキルのダメージ量(%)
		*/
		int GetDamage() const noexcept
		{
			return skillData_->DamagePercent;
		}

		/*
		* @brief	スキルが使用できるか？
		* @param	true　なら使用可能
		*/
		virtual bool CanUseSkill()
		{
			return canUse_.Get();
		}


		/**
		* @brief		CT変化通知
		*/
		ActionGame::IObservable<float>* GetCTSubject()			{ return &(CT_.Get()); }
		ActionGame::IObservable<float>* GetMaxCTSubject()		{ return &(skillData_->MaxCT.Get()); }
		ActionGame::IObservable<bool>* GetCanUseSubject()		{ return &(canUse_.Get()); }


		/////////////////////////////////////////////////////////////////////
		///			セッター
		////////////////////////////////////////////////////////////////////

		/**
		* @brief		スキル名を設定
		*/
		void SetKey(const std::string& key) noexcept
		{
			skillName_ = key;
			
		}

		/*
		* @brief		ステート名を取得
		* @param		state		ステート名
		* @param		flyState	空中ステート名
		*/
		void SetState(char* state, char* flyState) noexcept
		{
			stateName_ = state;
			flyStateName_ = flyState;
		}

		/*
		* @brief		インプットキー名を取得
		*/
		void SetButton(const std::string& button) noexcept
		{
			inputKey_ = button;
		}

		/*
		* @brief		現在のクールタイムを取得
		* @param		クールタイム(秒)
		*/
		void SetCT(float ct) noexcept
		{
			CT_ = ct;
		}
		/*
		* @brief		現在のクールタイムを減少
		* @param		減少させるクールタイム(秒)
		*/
		void SubCT(float ct) noexcept
		{
			CT_ = max(CT_.Get() - ct, 0.0f);
		}

		/*
		* @brief		最大のクールタイムを設定
		* @param		最大クールタイム(秒)
		*/
		void SetMaxCT(float ct) noexcept
		{
			skillData_->MaxCT = ct;
		}

		/*
		* @brief		スキルのダメージ量を設定
		* @param		damage スキルのダメージ量(%)
		*/
		void SetDamage(float damage) noexcept
		{
			skillData_->DamagePercent = damage;
		}

		/*
		* @brief		使用可能可否を設定
		* @param		true　なら使用可能
		*/
		void SetCanUse(bool isCanUse) noexcept
		{
			canUse_ = isCanUse;
		}

		/*
		* @brief		スキルデータを設定
		* @param		skill スキルデータ
		*/
		virtual void SetSkillData(const SkillDataPtr& skill)
		{
			skillData_ = skill;
		}

		/*
		* @brief		スキルデータを設定
		* @param		damage ダメージ量(%)
		* @param		ct	最大クールタイム(秒)
		*/
		void SetSkillData(float damage, float ct) noexcept
		{
			skillData_->MaxCT = ct;
			skillData_->DamagePercent = damage;
		}
		

	};

	//ポインタ置き換え
	using SKillPtr = std::shared_ptr<CSkill>;
	using SkillWeakPtr = std::weak_ptr<CSkill>;
}