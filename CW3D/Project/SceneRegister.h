#pragma once
#include "SceneCreator.h"

namespace ActionGame
{
	/**
	 * @brief		�V�[���o�^�p�C���^�[�t�F�C�X
	 */
	class __declspec(novtable) ISceneRegister
	{
	public:
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~ISceneRegister() = default;

		/**
		 * @brief		�V�[���o�^
		 * @param		sceneNo	�V�[���ԍ�
		 * @param		creator	�V�[�������N���X
		 */
		virtual void RegistScene(SCENENO sceneNo, SceneCreatorPtr creator) = 0;
	};
	using SceneRegisterPtr = std::shared_ptr<ISceneRegister>;
}
