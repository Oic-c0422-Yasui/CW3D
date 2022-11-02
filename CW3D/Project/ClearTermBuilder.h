#pragma once
#include "IClearTerm.h"
#include "ClearTermProvider.h"
#include "json.hpp"


namespace Sample
{
	class IClearTermBuilder
	{
	protected:

	public:
		virtual ~IClearTermBuilder() = default;

		virtual ClearTermPtr Create(nlohmann::json& os) = 0;
		virtual ClearTermPtr Create() = 0;
	};

	using ClearTermBuilderPtr = std::shared_ptr<IClearTermBuilder>;
}


