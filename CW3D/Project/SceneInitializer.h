#pragma once
#include "SceneBase.h"
#include "SceneChangeEffect.h"

namespace ActionGame
{
	/**
	 * @brief		�V�[���������p�C���^�[�t�F�C�X
	 */
	class __declspec(novtable) ISceneInitializer
	{
	public:
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~ISceneInitializer() = default;

		/**
		 * @brief		���݂̃V�[��������������
		 */
		virtual bool InitializeScene(SceneChangeEffectPtr effect) = 0;


	};
	using SceneInitializerPtr = std::shared_ptr<ISceneInitializer>;
}
