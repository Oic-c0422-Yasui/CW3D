#pragma once
#include	"Skill.h"


namespace ActionGame
{
	/*
	* @brief	追加入力が可能なスキル
	*/
	class AdditionalSkill : public Skill
	{
	private:
		float m_AddStartTime;
		ActionGame::ParameterHandle< ActionGame::ReactiveParameter<float> >	m_AddCT;
		int		m_AddCount;
		bool	m_AddFlg;
		bool	m_DelayAddFlg;
		AdditionalSkillDataPtr m_AddSkillData;
	public:
		AdditionalSkill();
		~AdditionalSkill();

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
			m_AddCT = time;
		}

		/*
		* @brief	最大追加クールタイムを設定
		* @param	time 最大追加クールタイム(秒)
		*/
		void SetAddMaxCT(float time) noexcept
		{
			m_AddSkillData->AddMaxCT = time;
		}

		/*
		* @brief	使用回数を設定
		*/
		void SetAddCount(float count) noexcept
		{
			m_AddCount = count;
		}

		/*
		* @brief	追加入力
		*/
		void AddInput()
		{
			SetAddCT(0.0f);
			m_AddFlg = false;
		}

		/*
		* @brief	追加入力
		*/
		bool IsAdditional() const noexcept
		{
			return m_AddFlg;
		}
		virtual bool IsDelayAdditional()
		{
			return m_DelayAddFlg;
		}

		float GetAddCT() const noexcept
		{
			return m_AddCT.Get();
		}
		float GetAddMaxCT() const noexcept
		{
			return m_AddSkillData->AddMaxCT.Get();
		}


		int GetAddCount() const noexcept
		{
			return m_AddCount;
		}

		/*
		* @brief	使用可能か？
		* @return	true　なら使用可能
		*/
		bool IsCanUse() override
		{
			return m_AddFlg | m_CanUseFlg.Get();
		}

		/*
		* @brief	スキルデータ設定
		*/
		void SetSkillData(const SkillDataPtr& skill) override;
		

		ActionGame::IObservable<float>* GetAddCTSubject() { return &(m_AddCT.Get()); }
		ActionGame::IObservable<float>* GetAddMaxCTSubject() { return &(m_AddSkillData->MaxCT.Get()); }

	};

	//ポインタ置き換え
	using AdditionalSKillPtr = std::shared_ptr<AdditionalSkill>;
	using AdditionalWeakSKillPtr = std::weak_ptr<AdditionalSkill>;
}