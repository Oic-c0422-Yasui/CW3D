#pragma once
#include	"ReactiveParameter.h"
#include	"ParameterHandle.h"

namespace ActionGame
{
	/*
	* スキルデータをまとめたクラス
	*/

	/*
	* @brief	スキルデータ
	*/
	struct SkillData
	{
		//ダメージ量（％）
		uint32_t	DamagePercent;
		//最大のクールタイム
		ParameterHandle< CReactiveParameter<float>>	MaxCT;
		SkillData()
			: DamagePercent(0)
			, MaxCT(0.0f)

		{
		}

		SkillData(uint32_t dmg, float maxCT)
			: DamagePercent(dmg)
			, MaxCT(maxCT)

		{
		}

		virtual ~SkillData(){}
	};
	using SkillDataPtr = std::shared_ptr<SkillData>;

	/*
	* @brief	追加スキルデータ
	*/
	struct AdditionalSkillData : public SkillData
	{
		//追加スキルの最大のクールタイム
		ParameterHandle< CReactiveParameter<float>>	AddMaxCT;
		//開始時間
		float StartTime;
		//追加する使用可能回数
		BYTE Count;
		AdditionalSkillData()
			: SkillData()
			, AddMaxCT(0)
			, StartTime(0)
			, Count(0)
		{
		}
		/*
		* @brief	コンストラクタ
		* @param	dmg ダメージ
		* @param	maxCT 最大クールタイム
		* @param	addMaxCT 追加入力クールタイム
		* @param	st	開始時間
		* @param	cnt	追加回数
		*/
		AdditionalSkillData(uint32_t dmg, float maxCT,float addmaxCT,float st,int cnt)
			: SkillData(dmg, maxCT)
			, AddMaxCT(addmaxCT)
			, StartTime(st)
			, Count(cnt)
		{
		}
	};
	using AdditionalSkillDataPtr = std::shared_ptr<AdditionalSkillData>;

	/*
	* @brief	必殺技スキルデータ
	*/
	struct UltimateSkillData : public SkillData
	{
		//使用するゲージ量
		ParameterHandle< CReactiveParameter<float>>	ExpendGauge;

		UltimateSkillData()
			: SkillData()
			, ExpendGauge(0)
		{
		}
		UltimateSkillData(uint32_t dmg, float maxCT,float gauge)
			: SkillData(dmg, maxCT)
			, ExpendGauge(gauge)
		{
		}
	};
	using UltimateSkillDataPtr = std::shared_ptr<UltimateSkillData>;

}

