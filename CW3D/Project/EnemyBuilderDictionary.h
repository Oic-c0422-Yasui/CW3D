#pragma once
#include "EnemyBuilder.h"

namespace ActionGame
{
	class EnemyBuilderDictionary
	{
	private:
		std::map<std::string, EnemyBuilderPtr> map_;
	public:
		EnemyBuilderDictionary();
		~EnemyBuilderDictionary();

		void Add(const std::string& name, const EnemyBuilderPtr& builder)
		{
			map_[name] = builder;
		}

		const EnemyBuilderPtr& Get(const std::string& name)
		{
			assert(map_[name]);
			return map_[name];
		}

		bool Delete(const std::string& name)
		{
			auto it = map_.find(name);
			if (it != map_.end())
			{
				map_.erase(it);
				return true;
			}
			return false;
		}
	};

}


