#pragma once
#include "Common.h"
#include <codecvt>

namespace MyUtil
{
	/*
	* @brief		UTF-8‚ðShiftJIS‚É•ÏŠ·
	*/
	std::string UTF8toShiftJIS(const std::string& utf8);


	/*
	* @brief		UTF-8‚ðUTF-16‚É•ÏŠ·
	*/
	std::u16string ConvertUTF8ToUTF16(const std::string& str);
}

