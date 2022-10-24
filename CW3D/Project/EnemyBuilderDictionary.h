#pragma once
#include "EnemyBuilder.h"

namespace Sample
{
	class EnemyBuilderDictionary
	{
	private:
		std::map<std::string, EnemyBuilderPtr> map;
	public:
		EnemyBuilderDictionary();
		~EnemyBuilderDictionary();

		void Add(const std::string& name, const EnemyBuilderPtr& builder)
		{
			map[name] = builder;
		}

		const EnemyBuilderPtr& Get(const std::string& name)
		{
			assert(map[name]);
			return map[name];
		}

		bool Delete(const std::string& name)
		{
			auto it = map.find(name);
			if (it != map.end())
			{
				map.erase(it);
				return true;
			}
			return false;
		}
	};

}


