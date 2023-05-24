#pragma once
#include "json.hpp"
#include "State.h"

namespace ActionGame
{
	/*
	* @brief	ステートのビルダー
	*/
	class __declspec(novtable) IStateBuilder
	{
	public:
		virtual ~IStateBuilder() = default;

		virtual StatePtr Create(nlohmann::json& os) = 0;
		virtual StatePtr Create() = 0;
	};

	using StateBuilderPtr = std::shared_ptr<IStateBuilder>;
}
