#pragma once
#include "IParameterCreator.h"
#include "ParameterDefine.h"

namespace ActionGame {

	/**
	 * @brief		�p�����[�^����
	 */
	class ZombieParameterCreator : public IParameterCreator
	{
	public:
		/**
		 * @brief		����
		 */
		bool Create(const AnyParameterMapPtr& param) override;
	};

}