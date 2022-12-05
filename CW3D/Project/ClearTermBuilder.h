#pragma once
#include "IClearTerm.h"
#include "ClearTermProvider.h"
#include "json.hpp"


namespace ActionGame
{
	/*
	* @brief	�N���A�����r���_�[
	*/
	class __declspec(novtable) IClearTermBuilder
	{
	public:
		virtual ~IClearTermBuilder() = default;

		virtual ClearTermPtr Create(nlohmann::json& os) = 0;
		virtual ClearTermPtr Create() = 0;
	};

	using ClearTermBuilderPtr = std::shared_ptr<IClearTermBuilder>;
}


