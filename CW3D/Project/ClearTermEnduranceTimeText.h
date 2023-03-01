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
        * @brief    �����`��ʒu��ݒ�
        */
        void SetDescriptionPos(const Vector2& pos)
        {
            descriptionPos_ = pos;
        }
        /*
        * @brief    �N���A�����`��ʒu��ݒ�
        */
        void SetClearTermPos(const Vector2& pos)
        {
            clearTermPos_ = pos;
        }
    };

    using EnduranceTimeTextPtr = std::shared_ptr<CEnduranceTimeText>;
}


