#pragma once
#include "ClearTermRender.h"

namespace Sample
{
    class ClearTermEnduranceTimeRender : public ClearTermRender
    {
    private:
        float m_CurrentTime;
        float m_FinishTime;
        Vector2 m_DescriptionPos;
        Vector2 m_CurrentTermPos;
    public:
        ClearTermEnduranceTimeRender();
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
    };

    using ClearTermEnduranceTimeRenderPtr = std::shared_ptr<ClearTermEnduranceTimeRender>;
}


