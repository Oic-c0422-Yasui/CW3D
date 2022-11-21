#pragma once
#include "ClearTermRender.h"

namespace Sample
{
    class ClearTermEnemyAllDeadRender : public ClearTermRender
    {
    private:
        int m_EnemyCount;
        int m_EnemyMaxCount;
    public:
        ClearTermEnemyAllDeadRender();

        void Initialize() override;
        void Render() override;

        void SetEnemyCount(int count) 
        {
            m_EnemyCount = count;
        }
        void SetEnemyMaxCount(int count)
        {
            m_EnemyMaxCount = count;
        }
    };

    using ClearTermEnemyAllDeadRenderPtr = std::shared_ptr<ClearTermEnemyAllDeadRender>;

}


