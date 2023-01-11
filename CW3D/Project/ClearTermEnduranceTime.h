#pragma once
#include "IClearTerm.h"

namespace ActionGame
{
	/*
	* @brief	�N���A����(���ԑϋv)
	*/
	class ClearTermEnduranceTime : public IClearTerm
	{
	private:
		float m_EnduranceTime;
	public:
		ClearTermEnduranceTime(float time);
		bool IsClear(const ClearTermProviderPtr& provider) override;

		const std::string& GetType() const noexcept override  { return "EnduranceTime"; }

	};
}


