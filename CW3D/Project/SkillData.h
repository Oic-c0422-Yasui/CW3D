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
		ParameterHandle< ReactiveParameter<int> >	DamagePercent;
		ParameterHandle< ReactiveParameter<float>>	CT;
		ParameterHandle< ReactiveParameter<float>>	AditionalTime;
		ParameterHandle< ReactiveParameter<int>>	StuckCount;
		int	AditionalCount;

		void SetData(float damage, float ct, float addTime, int stuckCount) noexcept
		{
			DamagePercent = damage;
			CT = ct;
			AditionalTime = addTime;
			StuckCount = stuckCount;
		}
	};

}

