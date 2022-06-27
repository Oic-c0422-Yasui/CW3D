#pragma once

#include	"IActor.h"

namespace Sample {

	/**
	 * @brief		�A�N�V���������C���^�[�t�F�C�X
	 */
	class __declspec(novtable) IActionCreator
	{
	public:
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~IActionCreator() = default;

		/**
		 * @brief		����
		 */
		virtual bool Create(const ActorPtr& actor) = 0;
	};
	//�|�C���^�u������
	using ActionCreatorPtr = std::shared_ptr<IActionCreator>;
}