#pragma once
#include "IParameterCreator.h"
#include "ParameterDefine.h"

namespace ActionGame
{
	/**
	 * @brief		�p�����[�^����
	 */
	class MutantParameterCreator :  public IParameterCreator
	{
	public:
		/**
		 * @brief		����
		 */
		bool Create(const AnyParameterMapPtr & param) override;
	};
}


