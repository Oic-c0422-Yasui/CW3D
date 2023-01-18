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
		 * @brief		�f�X�g���N�^
		 */
		virtual ~PlayerParameterCreator() = default;

		/**
		 * @brief		����
		 */
		bool Create(const AnyParameterMapPtr& param) override;
	};


}