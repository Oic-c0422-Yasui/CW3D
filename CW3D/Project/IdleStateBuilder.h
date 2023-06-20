#pragma once
#include "StateBuilder.h"

namespace ActionGame
{
    class IdleStateBuilder : public IStateBuilder
    {
    public:
        IdleStateBuilder();

        StatePtr Create(nlohmann::json& os) override;
        StatePtr Create() override;
    };

}


