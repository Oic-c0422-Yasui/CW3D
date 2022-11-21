#pragma once
#include "IClearTerm.h"

namespace Sample
{
	class ClearTermEnduranceTime : public IClearTerm
	{
	private:
		float m_EnduranceTime;
	public:
		ClearTermEnduranceTime(float time);
		bool IsClear(const ClearTermProviderPtr& provider) override;

		const std::string& GetType() override { return "EnduranceTime"; }

	};
}


