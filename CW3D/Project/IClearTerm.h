#pragma once

#include "ClearTermProvider.h"

namespace Sample
{
	
	class IClearTerm
	{
	protected:
		
	public:
		virtual bool IsClear(const ClearTermProviderPtr& provider) = 0;
		virtual ~IClearTerm() = default;
	};
	using ClearTermPtr = std::shared_ptr<IClearTerm>;
	using ClearTermArray = std::vector<ClearTermPtr>;
}

