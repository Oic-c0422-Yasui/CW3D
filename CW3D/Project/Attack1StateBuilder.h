#pragma once
#include "StateBuilder.h"
#include "Attack1State.h"
#include "StateBuilderUtilities.h"

namespace ActionGame
{
	class Attack1StateBuilder : public IStateBuilder
	{
	private:
		CAttack1State::Parameter param_;
	public:
		Attack1StateBuilder();

		StatePtr Create(nlohmann::json& os) override;
		StatePtr Create() override;
	};
}



