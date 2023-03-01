#pragma once
#include "IParameterCreator.h"
#include "ParameterDefine.h"

namespace ActionGame {

	/**
	 * @brief		パラメータ生成
	 */
	class ZombieParameterCreator : public IParameterCreator
	{
	public:
		/**
		 * @brief		生成
		 */
		bool Create(const AnyParameterMapPtr& param) override;
	};

}