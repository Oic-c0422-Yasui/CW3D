#pragma once
#include "SpawnerBuilder.h"

namespace Spawner
{
	/*
	* @brief	�X�|�i�[�r���_�[�̎���
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


