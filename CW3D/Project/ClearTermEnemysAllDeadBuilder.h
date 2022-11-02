#pragma once
#include "ClearTermBuilder.h"
#include "ClearTermEnemysAllDead.h"

namespace Sample
{
    class ClearTermEnemysAllDeadBuilder : public IClearTermBuilder
    {
    private:

    public:
        ClearTermEnemysAllDeadBuilder();

        ClearTermPtr Create(nlohmann::json& os) override;
        ClearTermPtr Create() override;
    };

}


