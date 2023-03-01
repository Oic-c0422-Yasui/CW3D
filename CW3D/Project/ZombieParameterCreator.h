#pragma once
#include "IParameterCreator.h"
#include "ParameterDefine.h"

namespace ActionGame {

	/**
	 * @brief		ƒpƒ‰ƒ[ƒ^¶¬
	 */
	class ZombieParameterCreator : public IParameterCreator
	{
	public:
		/**
		 * @brief		¶¬
		 */
		bool Create(const AnyParameterMapPtr& param) override;
	};

}