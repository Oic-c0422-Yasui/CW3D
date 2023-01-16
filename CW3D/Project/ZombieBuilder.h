#pragma once
#include "EnemyBuilder.h"

namespace ActionGame
{
    /*
    * @param    ゾンビビルダー
    */
    class ZombieBuilder : public EnemyBuilder
    {
    public:
		ZombieBuilder();
        
        /*
        * @param    生成
        */
        EnemyPtr Create(const EnemyBuildParameterPtr& param) override;
    };
}


