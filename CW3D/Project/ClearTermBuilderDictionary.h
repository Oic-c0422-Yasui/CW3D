#pragma once
#include "ClearTermBuilder.h"

namespace ClearTerm
{
	/*
	* @brief	クリア条件ビルダーの辞書
	*/
	class CBuilderDictionary
	{
	private:
		std::map<std::string, BuilderPtr> dictionary_;
	public:
		CBuilderDictionary();
		~CBuilderDictionary();

		const BuilderPtr& Get(const std::string& key)
		{
			return dictionary_[key];
		}


	};

}


