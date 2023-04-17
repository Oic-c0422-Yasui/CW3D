#pragma once
#include	"Skill.h"
#include	"IActor.h"


namespace ActionGame
{
	/*
	* @brief	必殺技スキル
	*/
	class UltimateSkill : public CSkill
	{
	private:

		bool isMaxGauge_;

		//所有者のアクター参照
		ActorWeakPtr actorRef_;

		UltimateSkillDataPtr ultSkillData_;
	public:
		/*
		* @brief	コンストラクタ
		* @param	actor	所有者のアクター
		*/
		UltimateSkill(const ActorWeakPtr& actor);
		
		~UltimateSkill();

		/*
		* @brief	スキル生成
		* @param	key スキル名
		* @param	inputKey インプットキー名
		* @param	texName	スキルテクスチャの名前
		* @param	state	ステート名
		* @param	state	空中ステート名
		*/
		void Create(const std::string& key, const std::string& inputKey, const std::string& texName, char* state, char* flyState) override;

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
		* @brief	使用する必殺技ゲージ取得
		*/
		float GetExpendGauge() const noexcept
		{
			return ultSkillData_->ExpendGauge.Get();
		}

		/*
		* @brief	スキルデータ設定
		* @param	skill	スキルデータ
		*/
		void SetSkillData(const SkillDataPtr& skill) override
		{
			CSkill::SetSkillData(skill);
			ultSkillData_ = std::dynamic_pointer_cast<UltimateSkillData>(skillData_);
			if (ultSkillData_ == nullptr)
			{
				assert(ultSkillData_);
			}
		}

		/*
		* @brief	使用する必殺技ゲージ通知
		*/
		ActionGame::IObservable<float>* GetSkillUltSubject(int id) { return &(ultSkillData_->ExpendGauge.Get()); }
	};

	//ポインタ置き換え
	using UltimateSkillPtr = std::shared_ptr<UltimateSkill>;
	using UltimateWeakSkillPtr = std::weak_ptr<UltimateSkill>;
}