#pragma once

namespace Sample
{
	class CSkillData
	{
	public:
		int DamagePercent;
		int CT;

	};

	using SkillDataPtr = std::shared_ptr<CSkillData>;
}

