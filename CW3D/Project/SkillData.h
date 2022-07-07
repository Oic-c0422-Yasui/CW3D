#pragma once
#include	"ReactiveParameter.h"
#include	"ParameterHandle.h"

namespace Sample
{
	class CSkillData
	{
	public:
		CSkillData()
			: DamagePercent(0)
			, CT(0.0f)
			, AditionalTime(0.0f)
			, AditionalCount(0)
			, StuckCount(0)
		{
		}
		int	DamagePercent;
		float AditionalStartTime;
		ParameterHandle< ReactiveParameter<float>>	CT;
		ParameterHandle< ReactiveParameter<float>>	AditionalTime;
		ParameterHandle< ReactiveParameter<int>>	StuckCount;
		ParameterHandle< ReactiveParameter<float>>	ExpendGauge;
		int	AditionalCount;
		void SetData(float damage, float ct, float gauge) noexcept
		{
			DamagePercent = damage;
			CT = ct;
			ExpendGauge = gauge;
		}
		void SetData(float damage, float ct, float addTime, float addStartTime, int stuckCount) noexcept
		{
			DamagePercent = damage;
			CT = ct;
			AditionalTime = addTime;
			AditionalStartTime = addStartTime;
			StuckCount = stuckCount;
		}
	};

}

