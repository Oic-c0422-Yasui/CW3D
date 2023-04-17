#pragma once
#include "Common.h"
#include <codecvt>

namespace MyUtil
{
	/*
	* @brief		UTF-8��ShiftJIS�ɕϊ�
	*/
	std::string UTF8toShiftJIS(const std::string& utf8);


	/*
	* @brief		UTF-8��UTF-16�ɕϊ�
	*/
	std::u16string ConvertUTF8ToUTF16(const std::string& str);
}

