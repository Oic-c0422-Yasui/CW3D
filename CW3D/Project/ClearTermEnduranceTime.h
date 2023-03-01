#pragma once
#include "IClearTerm.h"

namespace ClearTerm
{
	/*
	* @brief	�N���A����(���ԑϋv)
	*/
	class CEnduranceTime : public IClearTerm
	{
	private:
		float enduranceTime_;
	public:
		CEnduranceTime(float time);
		bool IsClear(const ClearTerm::ProviderPtr& provider) override;

		const std::string& GetType() const noexcept override  { return "EnduranceTime"; }

	};
}


