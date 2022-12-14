#pragma once

#include	"ParameterMap.h"
#include "ReactiveParameter.h"

namespace ActionGame {

	/**
	 * @brief		パラメーター生成インターフェイス
	 */
	class __declspec(novtable) IParameterCreator
	{
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~IParameterCreator() = default;

		/**
		 * @brief		生成
		 */
		virtual bool Create(const AnyParameterMapPtr& param) = 0;
	};
	//ポインタ置き換え
	using ParameterCreatorPtr = std::shared_ptr<IParameterCreator>;
}