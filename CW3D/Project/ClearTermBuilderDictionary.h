#pragma once
#include "ClearTermBuilder.h"

namespace ActionGame
{
	/*
	* @brief	�N���A�����r���_�[�̎���
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


