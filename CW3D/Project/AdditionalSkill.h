#pragma once
#include	"Skill.h"


namespace ActionGame
{
	/*
	* @brief	追加入力が可能なスキル
	*/
	class CAdditionalSkill : public CSkill
	{
	private:
		float addStartTime_;
		ActionGame::ParameterHandle< ActionGame::CReactiveParameter<float> >	addCT_;
		int		addCount_;
		bool	isAdd_;
		bool	isDelayAdd_;
		AdditionalSkillDataPtr addSkillData_;
	public:
		CAdditionalSkill();
		~CAdditionalSkill();

		/*
		* @brief	開始
		*/
		void Start() override;

		/*
		* @brief	リセット
		*/
		void Reset() override;

		/*
		* @brief	更新
		*/
		void Update() override;

		/*
		* @brief	追加クールタイムを設定
		* @param	time 追加クールタイム(秒)
		*/
		void SetAddCT(float time) noexcept
		{
			addCT_ = time;
		}

		/*
		* @brief	最大追加クールタイムを設定
		* @param	time 最大追加クールタイム(秒)
		*/
		void SetAddMaxCT(float time) noexcept
		{
			addSkillData_->AddMaxCT = time;
		}

		/*
		* @brief	使用回数を設定
		*/
		void SetAddCount(float count) noexcept
		{
			addCount_ = count;
		}

		/*
		* @brief	追加入力
		*/
		void AddInput()
		{
			SetAddCT(0.0f);
			isAdd_ = false;
		}

		/*
		* @brief	追加入力
		*/
		bool IsAdditional() const noexcept
		{
			return isAdd_;
		}
		virtual bool IsDelayAdditional()
		{
			return isDelayAdd_;
		}

		float GetAddCT() const noexcept
		{
			return addCT_.Get();
		}
		float GetAddMaxCT() const noexcept
		{
			return addSkillData_->AddMaxCT.Get();
		}


		int GetAddCount() const noexcept
		{
			return addCount_;
		}

		/*
		* @brief	使用可能か？
		* @return	true　なら使用可能
		*/
		bool CanUseSkill() override
		{
			return isAdd_ | canUse_.Get();
		}

		/*
		* @brief	スキルデータ設定
		*/
		void SetSkillData(const SkillDataPtr& skill) override;
		

		ActionGame::IObservable<float>* GetAddCTSubject() { return &(addCT_.Get()); }
		ActionGame::IObservable<float>* GetAddMaxCTSubject() { return &(addSkillData_->MaxCT.Get()); }

	};

	//ポインタ置き換え
	using AdditionalSKillPtr = std::shared_ptr<CAdditionalSkill>;
	using AdditionalWeakSKillPtr = std::weak_ptr<CAdditionalSkill>;
}