#pragma once

#include	<memory>

namespace Sample
{
	/**
	 * @brief		周期決定処理
	 */
	class __declspec(novtable) IAICycle
	{
	public:
		/**
		 * @brief		更新
		 * @return		trueなら判定
		 */
		virtual bool Update() = 0;
		/**
		 * @brief		状態リセット
		 */
		virtual void Reset() = 0;
	};
	//ポインタ置き換え
	using AICyclePtr = std::shared_ptr<IAICycle>;
}
