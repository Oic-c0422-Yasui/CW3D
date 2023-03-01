#pragma once
#include "IParameterCreator.h"




namespace ActionGame {

	/**
	 * @brief		ƒpƒ‰ƒ[ƒ^¶¬
	 */
	class PlayerParameterCreator : public IParameterCreator
	{
	public:
		/**
		 * @brief		¶¬
		 */
		bool Create(const AnyParameterMapPtr& param) override;
	};


}