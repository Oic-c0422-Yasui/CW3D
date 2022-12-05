#pragma once
#include "ClearTermText.h"

namespace ActionGame
{
    class ClearTermEnduranceTimeText : public ClearTermText
    {
    private:
        float m_CurrentTime;
        float m_FinishTime;
        Vector2 m_DescriptionPos;
        Vector2 m_ClearTermPos;
    public:
        ClearTermEnduranceTimeText();
        void Initialize() override;
        void Render() override;
        void SetCurrentTime(float time)
        {
            m_CurrentTime = time;
        }
        void SetFinishTime(float time)
        {
            m_FinishTime = time;
        }
        /*
        * @brief    �����`��ʒu��ݒ�
        */
        void SetDescriptionPos(const Vector2& pos)
        {
            m_DescriptionPos = pos;
        }
        /*
        * @brief    �N���A�����`��ʒu��ݒ�
        */
        void SetClearTermPos(const Vector2& pos)
        {
            m_ClearTermPos = pos;
        }
    };

    using ClearTermEnduranceTimeTextPtr = std::shared_ptr<ClearTermEnduranceTimeText>;
}


