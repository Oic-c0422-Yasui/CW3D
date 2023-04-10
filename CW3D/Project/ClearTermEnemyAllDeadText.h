#pragma once
#include "ClearTermText.h"

namespace ClearTerm
{
    class CEnemyAllDeadText : public CClearTermText
    {
    private:
        size_t enemyCount_;
        size_t enemyMaxCount_;
        Vector2 descriptionPos_;
        Vector2 clearTermPos_;
    public:
        CEnemyAllDeadText();

        void Initialize() override;
        void Render() override;

        void SetEnemyCount(size_t count)
        {
            enemyCount_ = count;
        }
        void SetEnemyMaxCount(size_t count)
        {
            enemyMaxCount_ = count;
        }
        /*
       * @brief    説明描画位置を設定
       */
        void SetDescriptionPos(const Vector2& pos)
        {
            descriptionPos_ = pos;
        }
        /*
        * @brief    クリア条件描画位置を設定
        */
        void SetClearTermPos(const Vector2& pos)
        {
            clearTermPos_ = pos;
        }


    };

    using EnemyAllDeadTextPtr = std::shared_ptr<CEnemyAllDeadText>;

}


