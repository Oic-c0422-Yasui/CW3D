#pragma once

#include	"IScene.h"

namespace Scene
{
	/**
	 * @brief		�V�[���ύX�p�C���^�[�t�F�C�X
	 */
	class __declspec(novtable) ISceneChanger
	{
	public:
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~ISceneChanger() = default;

		/**
		 * @brief		�V�[���ύX
		 * @param		�V�[���ԍ�
		 */
		virtual bool ChangeScene(SCENENO sceneNo) = 0;

		/**
		 * @brief		�V�[���ύX(���[�h��ʂ�����)
		 * @param		sceneNo �V�[���ԍ�
		 * @param		isLoading ���[�h��ʂ����ނ��H
		 */
		virtual bool ChangeScene(SCENENO sceneNo,bool isLoading) = 0;
		
		/**
		 * @brief		�V�[���ύX�i���[�h�A�������͍s��Ȃ��j
		 * @param		scene ���[�h�ς݃V�[��
		 */
		virtual bool ChangeScene(const ScenePtr& scene) = 0;

	};
	using SceneChangerPtr = std::shared_ptr<ISceneChanger>;
}


