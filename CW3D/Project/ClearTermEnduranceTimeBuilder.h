#pragma once
#include "ClearTermBuilder.h"
#include "ClearTermEnduranceTime.h"

namespace ClearTerm
{
	/*
	* @brief	�N���A�����r���_�[(���ԑϋv)
	*/
	class CEnduranceTimeBuilder : public ClearTerm::IClearTermBuilder
	{
	private:
		float enduranceTime_;
	public:
		CEnduranceTimeBuilder();

		ClearTermPtr Create(nlohmann::json& os);
		ClearTermPtr Create();
	};
}


