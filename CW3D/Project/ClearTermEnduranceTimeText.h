#pragma once
#include "ClearTermText.h"

namespace ClearTerm
{
    class CEnduranceTimeText : public CClearTermText
    {
    private:
        float currentTime_;
        float finishTime_;
        Vector2 descriptionPos_;
        Vector2 clearTermPos_;
    public:
        CEnduranceTimeText();
        void Initialize() override;
        void Render() override;
        void SetCurrentTime(float time)
        {
            currentTime_ = time;
        }
        void SetFinishTime(float time)
        {
            finishTime_ = time;
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

    using EnduranceTimeTextPtr = std::shared_ptr<CEnduranceTimeText>;
}


