#pragma once
#include "EnemyBuilder.h"

namespace ActionGame
{
    /*
    * @param    �]���r�r���_�[
    */
    class ZombieBuilder : public EnemyBuilder
    {
    public:
		ZombieBuilder();
        
        /*
        * @param    ����
        */
        EnemyPtr Create(const EnemyBuildParameterPtr& param) override;
    };
}


