#include "ClearTermEnduranceTime.h"


Sample::ClearTermEnduranceTime::ClearTermEnduranceTime(float time)
    :m_EnduranceTime(time)
{
}

bool Sample::ClearTermEnduranceTime::IsClear(const ClearTermProviderPtr& provider)
{
    return false;
}
