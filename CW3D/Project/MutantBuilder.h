#pragma once
#include "EnemyBuilder.h"


namespace ActionGame
{
    class MutantBuilder : public EnemyBuilder
    {
    public:
        /**
         * @brief		コンストラクタ
         */
        MutantBuilder();
        /*
        * @param    生成
        */
        EnemyPtr Create(const EnemyBuildParameterPtr& param) override;
    };
}



