#pragma once
#include "ClearTermText.h"

namespace ActionGame
{
    class ClearTermEnemyAllDeadText : public ClearTermText
    {
    private:
        int m_EnemyCount;
        int m_EnemyMaxCount;
        Vector2 m_DescriptionPos;
        Vector2 m_ClearTermPos;
    public:
        ClearTermEnemyAllDeadText();

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
        /*
       * @brief    説明描画位置を設定
       */
        void SetDescriptionPos(const Vector2& pos)
        {
            m_DescriptionPos = pos;
        }
        /*
        * @brief    クリア条件描画位置を設定
        */
        void SetClearTermPos(const Vector2& pos)
        {
            m_ClearTermPos = pos;
        }


    };

    using ClearTermEnemyAllDeadTextPtr = std::shared_ptr<ClearTermEnemyAllDeadText>;

}


