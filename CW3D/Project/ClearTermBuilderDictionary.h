#pragma once
#include "ClearTermBuilder.h"

namespace Sample
{
	class ClearTermBuilderDictionary
	{
	private:
		std::map<std::string, ClearTermBuilderPtr> dictionary;
	public:
		ClearTermBuilderDictionary();
		~ClearTermBuilderDictionary();

		const ClearTermBuilderPtr& Get(const std::string& key)
		{
			return dictionary[key];
		}


	};

}


