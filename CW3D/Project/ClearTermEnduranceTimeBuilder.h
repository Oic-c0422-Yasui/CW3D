#pragma once
#include "ClearTermBuilder.h"
#include "ClearTermEnduranceTime.h"

namespace Sample
{
	/*
	* @brief	クリア条件ビルダー(時間耐久)
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


