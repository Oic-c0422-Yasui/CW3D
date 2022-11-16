#pragma once

#include "ClearTermProvider.h"

namespace Sample
{
	
	class __declspec(novtable) IClearTerm
	{
	public:

		virtual bool IsClear(const ClearTermProviderPtr& provider) = 0;
		virtual const std::string& GetDescription() = 0;
		virtual ~IClearTerm() = default;
	};
	using ClearTermPtr = std::shared_ptr<IClearTerm>;
	using ClearTermArray = std::vector<ClearTermPtr>;
}

