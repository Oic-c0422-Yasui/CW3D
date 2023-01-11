#pragma once

#include "ClearTermProvider.h"
#include <vector>
#include <string>

namespace ActionGame
{
	/*
	* @brief	ƒNƒŠƒAğŒ
	*/
	class __declspec(novtable) IClearTerm
	{
	public:
		virtual ~IClearTerm() = default;

		virtual bool IsClear(const ClearTermProviderPtr& provider) = 0;
		virtual const std::string& GetType() const noexcept = 0;
	};
	using ClearTermPtr = std::shared_ptr<IClearTerm>;
	using ClearTermArray = std::vector<ClearTermPtr>;
}

