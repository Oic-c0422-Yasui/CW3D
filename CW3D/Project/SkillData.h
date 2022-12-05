#pragma once
#include	"ReactiveParameter.h"
#include	"ParameterHandle.h"

namespace ActionGame
{

	struct SkillData
	{
		int	DamagePercent;
		ParameterHandle< ReactiveParameter<float>>	MaxCT;
		SkillData()
			: DamagePercent(0)
			, MaxCT(0.0f)

		{
		}

		SkillData(int dmg, float maxCT)
			: DamagePercent(dmg)
			, MaxCT(maxCT)

		{
		}

		virtual ~SkillData(){}
	};
	using SkillDataPtr = std::shared_ptr<SkillData>;

	struct AdditionalSkillData : public SkillData
	{
		ParameterHandle< ReactiveParameter<float>>	AddMaxCT;
		float StartTime;
		int Count;
		AdditionalSkillData()
			: SkillData()
			, AddMaxCT(0)
			, StartTime(0)
			, Count(0)
		{
		}

		AdditionalSkillData(int dmg, float maxCT,float addmaxCT,float st,int cnt)
			: SkillData(dmg, maxCT)
			, AddMaxCT(addmaxCT)
			, StartTime(st)
			, Count(cnt)
		{
		}
	};
	using AdditionalSkillDataPtr = std::shared_ptr<AdditionalSkillData>;

	struct UltimateSkillData : public SkillData
	{
		ParameterHandle< ReactiveParameter<float>>	ExpendGauge;
		UltimateSkillData()
			: SkillData()
			, ExpendGauge(0)
		{
		}
		UltimateSkillData(int dmg, float maxCT,float gauge)
			: SkillData(dmg, maxCT)
			, ExpendGauge(gauge)
		{
		}
	};
	using UltimateSkillDataPtr = std::shared_ptr<UltimateSkillData>;

}

