#include "ClearTermEnduranceTime.h"
#include "TimeScaleController.h"

Sample::ClearTermEnduranceTime::ClearTermEnduranceTime(float time)
    :   m_EnduranceTime(time)
{
}

bool Sample::ClearTermEnduranceTime::IsClear(const ClearTermProviderPtr& provider)
{

    if (provider->GetDivisionTime() <= m_EnduranceTime)
    {
        return true;
    }

    return false;
}
