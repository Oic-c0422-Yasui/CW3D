#pragma once
#include "ClearTermBuilder.h"
#include "ClearTermBossDead.h"

namespace ClearTerm
{
	class CBossDeadBuilder : public IClearTermBuilder
	{
	private:

	public:
		CBossDeadBuilder();
		ClearTermPtr Create(nlohmann::json& os) override;
		ClearTermPtr Create() override;
	};
}


