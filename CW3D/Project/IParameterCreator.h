#pragma once

#include	"ParameterMap.h"
#include "ReactiveParameter.h"

namespace ActionGame {

	/**
	 * @brief		�p�����[�^�[�����C���^�[�t�F�C�X
	 */
	class __declspec(novtable) IParameterCreator
	{
	public:
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~IParameterCreator() = default;

		/**
		 * @brief		����
		 */
		virtual bool Create(const AnyParameterMapPtr& param) = 0;
	};
	//�|�C���^�u������
	using ParameterCreatorPtr = std::shared_ptr<IParameterCreator>;
}