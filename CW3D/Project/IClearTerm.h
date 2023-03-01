#pragma once

#include "ClearTermProvider.h"
#include <vector>
#include <string>

namespace ClearTerm
{
	/*
	* @brief	クリア条件のインタフェース
	*/
	class __declspec(novtable) IClearTerm
	{
	public:
		virtual ~IClearTerm() = default;
		/*
		* @brief	クリア条件を満たしているか？
		* @param	provider クリア判定に必要な情報のプロバイダ
		*/
		virtual bool IsClear(const ProviderPtr& provider) = 0;
		/*
		* @brief	クリア条件の種類
		*/
		virtual const std::string& GetType() const noexcept = 0;
	};
	using ClearTermPtr = std::shared_ptr<IClearTerm>;
	using ClearTermArray = std::vector<ClearTermPtr>;
}

