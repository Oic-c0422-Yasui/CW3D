#pragma once
#include "IParameterCreator.h"




namespace ActionGame {

	/**
	 * @brief		�p�����[�^����
	 */
	class PlayerParameterCreator : public IParameterCreator
	{
	public:
		/**
		 * @brief		����
		 */
		bool Create(const AnyParameterMapPtr& param) override;
	};


}