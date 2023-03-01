#pragma once
#include "ClearTermBuilder.h"
#include "ClearTermEnduranceTime.h"

namespace ClearTerm
{
	/*
	* @brief	クリア条件ビルダー(時間耐久)
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


