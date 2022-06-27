#pragma once

#include	"IActor.h"

namespace Sample {

	/**
	 * @brief		アクション生成インターフェイス
	 */
	class __declspec(novtable) IActionCreator
	{
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~IActionCreator() = default;

		/**
		 * @brief		生成
		 */
		virtual bool Create(const ActorPtr& actor) = 0;
	};
	//ポインタ置き換え
	using ActionCreatorPtr = std::shared_ptr<IActionCreator>;
}