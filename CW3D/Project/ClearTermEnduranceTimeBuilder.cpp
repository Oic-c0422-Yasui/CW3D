#include "ClearTermEnduranceTimeBuilder.h"

Sample::ClearTermEnduranceTimeBuilder::ClearTermEnduranceTimeBuilder()
	: m_EnduranceTime(0.0f)
{
}

Sample::ClearTermPtr Sample::ClearTermEnduranceTimeBuilder::Create(nlohmann::json& os)
{
	os["Time"].get_to(m_EnduranceTime);

	return Create();
}

Sample::ClearTermPtr Sample::ClearTermEnduranceTimeBuilder::Create()
{
	ClearTermPtr clearTerm;
	clearTerm = std::make_shared<ClearTermEnduranceTime>(m_EnduranceTime);
	return clearTerm;
}
