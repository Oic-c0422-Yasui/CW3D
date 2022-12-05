#include "ClearTermEnduranceTime.h"
#include "TimeScaleController.h"

ActionGame::ClearTermEnduranceTime::ClearTermEnduranceTime(float time)
    :   m_EnduranceTime(time)
{
}

bool ActionGame::ClearTermEnduranceTime::IsClear(const ClearTermProviderPtr& provider)
{

    if (provider->GetDivisionTime() >= m_EnduranceTime)
    {
        float t = provider->GetDivisionTime();

        return true;
    }

    return false;
}
