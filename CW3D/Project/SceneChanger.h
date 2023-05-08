#pragma once

#include	"IScene.h"
#include	"SceneChangeEffect.h"

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
		virtual bool ChangeScene(SCENE_NO sceneNo) = 0;

		/**
		 * @brief		�V�[���ύX
		 * @param		�V�[���ԍ�
		 * @param		�V�[���J�ڃG�t�F�N�g
		 */
		virtual bool ChangeScene(SCENE_NO sceneNo,SceneChangeEffectPtr effect) = 0;

		/**
		 * @brief		�V�[���ύX(���[�h��ʂ�����)
		 * @param		sceneNo �V�[���ԍ�
		 * @param		�V�[���J�ڃG�t�F�N�g
		 * @param		isLoading ���[�h��ʂ����ނ��H
		 */
		virtual bool ChangeScene(SCENE_NO sceneNo,SceneChangeEffectPtr effect,bool isLoading) = 0;
		
		/**
		 * @brief		�V�[���ύX�i�ǂݍ��݁A�������͍s��Ȃ��j
		 * @param		scene ���[�h�ς݃V�[��
		 */
		virtual bool ChangeScene(const ScenePtr& scene, SceneChangeEffectPtr effect) = 0;

	};
	using SceneChangerPtr = std::shared_ptr<ISceneChanger>;
}


