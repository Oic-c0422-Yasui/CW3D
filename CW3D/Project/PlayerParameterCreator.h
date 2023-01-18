#pragma once
#include "IParameterCreator.h"




namespace ActionGame {

	/**
	 * @brief		パラメータ生成
	 */
	class PlayerParameterCreator : public IParameterCreator
	{
	public:
		/**
		 * @brief		デストラクタ
		 */
		virtual ~PlayerParameterCreator() = default;

		/**
		 * @brief		生成
		 */
		bool Create(const AnyParameterMapPtr& param) override;
	};


}