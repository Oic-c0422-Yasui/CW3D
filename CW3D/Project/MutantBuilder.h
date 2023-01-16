#pragma once
#include "EnemyBuilder.h"


namespace ActionGame
{
    class MutantBuilder : public EnemyBuilder
    {
    public:
        MutantBuilder();

        /*
        * @param    ����
        */
        EnemyPtr Create(const EnemyBuildParameterPtr& param) override;
    };
}



