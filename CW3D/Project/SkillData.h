#pragma once

namespace Sample
{
	class CSkillData
	{

	public:
		CSkillData()
			: DamagePercent(0)
			, CT(0.0f)
		{
		}
		int		DamagePercent;
		float	CT;
	};

	using SkillDataPtr = std::shared_ptr<CSkillData>;
}

