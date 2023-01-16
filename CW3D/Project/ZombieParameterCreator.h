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
		 * @brief		�f�X�g���N�^
		 */
		virtual ~ZombieParameterCreator() = default;

		/**
		 * @brief		����
		 */
		bool Create(const AnyParameterMapPtr& param) override;
	};

}