#pragma once
#include "SpawnerBuilder.h"

namespace Spawner
{
	/*
	* @brief	スポナービルダーの辞書
	*/
	class CBuilderDictionary
	{
	private:
		std::unordered_map<std::string, SpawnerBuilderPtr> dictionary_;
	public:
		CBuilderDictionary();
		~CBuilderDictionary();

		const SpawnerBuilderPtr& Get(const std::string& key)
		{
			assert(dictionary_[key]);
			return dictionary_[key];
		}
	};

}


