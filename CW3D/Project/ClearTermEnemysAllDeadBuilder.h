#pragma once
#include "ClearTermBuilder.h"
#include "ClearTermEnemysAllDead.h"

namespace ActionGame
{
    /*
    * @brief    クリア条件ビルダー(敵をすべて倒す)
    */
    class ClearTermEnemysAllDeadBuilder : public IClearTermBuilder
    {
    private:

    public:
        ClearTermEnemysAllDeadBuilder();

        ClearTermPtr Create(nlohmann::json& os) override;
        ClearTermPtr Create() override;
    };

}


