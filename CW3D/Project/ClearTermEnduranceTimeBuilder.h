#pragma once
#include "ClearTermBuilder.h"
#include "ClearTermEnduranceTime.h"

namespace ActionGame
{
	/*
	* @brief	�N���A�����r���_�[(���ԑϋv)
	*/
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


