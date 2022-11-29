#pragma once

#include "ClearTermProvider.h"

namespace Sample
{
	/*
	* @brief	�N���A����
	*/
	class __declspec(novtable) IClearTerm
	{
	public:
		virtual ~IClearTerm() = default;

		virtual bool IsClear(const ClearTermProviderPtr& provider) = 0;
		virtual const std::string& GetType() = 0;
	};
	using ClearTermPtr = std::shared_ptr<IClearTerm>;
	using ClearTermArray = std::vector<ClearTermPtr>;
}

