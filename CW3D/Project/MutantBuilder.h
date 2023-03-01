#pragma once
#include "EnemyBuilder.h"


namespace ActionGame
{
    class MutantBuilder : public EnemyBuilder
    {
    public:
        /**
         * @brief		�R���X�g���N�^
         */
        MutantBuilder();
        /*
        * @param    ����
        */
        EnemyPtr Create(const EnemyBuildParameterPtr& param) override;
    };
}



