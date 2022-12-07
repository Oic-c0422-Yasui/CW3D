#pragma once
#include "SceneCreator.h"
#include "GameDefine.h"

namespace ActionGame
{
	/**
	 * @brief		�V�[���o�^�p���ʃC���^�[�t�F�C�X
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
		 */
		virtual void RegistScene(tag_SCENENO sceneNo, SceneCreatorPtr creator) = 0;
	};
	using SceneRegisterPtr = std::shared_ptr<ISceneRegister>;
}
