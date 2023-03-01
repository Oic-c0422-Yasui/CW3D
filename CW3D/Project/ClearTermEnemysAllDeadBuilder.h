#pragma once
#include "ClearTermBuilder.h"
#include "ClearTermEnemysAllDead.h"

namespace ClearTerm
{
    /*
    * @brief    �N���A�����r���_�[(�G�����ׂē|��)
    */
    class CEnemysAllDeadBuilder : public IClearTermBuilder
    {
    public:
        CEnemysAllDeadBuilder();

        ClearTermPtr Create(nlohmann::json& os) override;
        ClearTermPtr Create() override;
    };

}


