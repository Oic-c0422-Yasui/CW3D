#pragma once
#include "ClearTermBuilder.h"
#include "ClearTermEnemysAllDead.h"

namespace ClearTerm
{
    /*
    * @brief    クリア条件ビルダー(敵をすべて倒す)
    */
    class CEnemysAllDeadBuilder : public IClearTermBuilder
    {
    public:
        CEnemysAllDeadBuilder();

        ClearTermPtr Create(nlohmann::json& os) override;
        ClearTermPtr Create() override;
    };

}


