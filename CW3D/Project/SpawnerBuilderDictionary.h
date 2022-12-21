#pragma once
#include "SpawnerBuilder.h"

namespace Spawner
{
	/*
	* @brief	スポナービルダーの辞書
	*/
	class SpawnerBuilderDictionary
	{
	private:
		std::unordered_map<std::string, SpawnerBuilderPtr> dictionary;
	public:
		SpawnerBuilderDictionary();
		~SpawnerBuilderDictionary();

		const SpawnerBuilderPtr& Get(const std::string& key)
		{
			assert(dictionary[key]);
			return dictionary[key];
		}
	};

}


