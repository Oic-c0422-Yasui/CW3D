#pragma once
#include "ClearTermBuilder.h"
#include "ClearTermEnduranceTime.h"

namespace Sample
{
	class ClearTermEnduranceTimeBuilder : public IClearTermBuilder
	{
	private:
		float m_EnduranceTime;
	public:
		ClearTermEnduranceTimeBuilder();

		ClearTermPtr Create(nlohmann::json& os);
		ClearTermPtr Create();
	};
}


