#pragma once
#include "ClearTermBuilder.h"

namespace ActionGame
{
	/*
	* @brief	クリア条件ビルダーの辞書
	*/
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


