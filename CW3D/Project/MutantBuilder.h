#pragma once
#include "EnemyBuilder.h"


namespace ActionGame
{
    class MutantBuilder : public EnemyBuilder
    {
    public:
        MutantBuilder();

        /*
        * @param    ê∂ê¨
        */
        EnemyPtr Create(const EnemyBuildParameterPtr& param) override;
    };
}



