#pragma once
#include "ClearTermBuilder.h"
#include "ClearTermEnemysAllDead.h"

namespace Sample
{
    /*
    * @brief    �N���A�����r���_�[(�G�����ׂē|��)
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


