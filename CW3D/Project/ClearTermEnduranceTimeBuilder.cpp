#include "ClearTermEnduranceTimeBuilder.h"

ClearTerm::CEnduranceTimeBuilder::CEnduranceTimeBuilder()
	: enduranceTime_(0.0f)
{
}

ClearTerm::ClearTermPtr ClearTerm::CEnduranceTimeBuilder::Create(nlohmann::json& os)
{
	os["Time"].get_to(enduranceTime_);

	return Create();
}

ClearTerm::ClearTermPtr ClearTerm::CEnduranceTimeBuilder::Create()
{
	ClearTermPtr clearTerm;
	clearTerm = std::make_shared<ClearTerm::CEnduranceTime>(enduranceTime_);
	return clearTerm;
}
