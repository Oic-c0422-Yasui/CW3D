#include "ClearTermEnduranceTime.h"
#include "TimeScaleController.h"

ClearTerm::CEnduranceTime::CEnduranceTime(float time)
    :   enduranceTime_(time)
{
}

bool ClearTerm::CEnduranceTime::IsClear(const ClearTerm::ProviderPtr& provider)
{

    if (provider->GetDivisionTime() >= enduranceTime_)
    {
        return true;
    }

    return false;
}
