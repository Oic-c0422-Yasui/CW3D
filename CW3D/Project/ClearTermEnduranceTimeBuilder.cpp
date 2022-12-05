#include "ClearTermEnduranceTimeBuilder.h"

ActionGame::ClearTermEnduranceTimeBuilder::ClearTermEnduranceTimeBuilder()
	: m_EnduranceTime(0.0f)
{
}

ActionGame::ClearTermPtr ActionGame::ClearTermEnduranceTimeBuilder::Create(nlohmann::json& os)
{
	os["Time"].get_to(m_EnduranceTime);

	return Create();
}

ActionGame::ClearTermPtr ActionGame::ClearTermEnduranceTimeBuilder::Create()
{
	ClearTermPtr clearTerm;
	clearTerm = std::make_shared<ClearTermEnduranceTime>(m_EnduranceTime);
	return clearTerm;
}
