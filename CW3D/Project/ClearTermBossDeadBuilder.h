#pragma once
#include "ClearTermBuilder.h"
#include "ClearTermBossDead.h"

namespace ActionGame
{
	class ClearTermBossDeadBuilder : public IClearTermBuilder
	{
	private:

	public:
		ClearTermBossDeadBuilder();
		ClearTermPtr Create(nlohmann::json& os) override;
		ClearTermPtr Create() override;
	};
}


