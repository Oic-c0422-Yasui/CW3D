#pragma once
#include "ISceneManager.h"
#include "SceneCreator.h"
#include <unordered_map>
#include "ThreadCreator.h"
#include "TaskManager.h"

namespace Scene
{
	/**
	 * �V�[���}�l�[�W���[
	 */
	class CSceneManager : public ISceneManager
	{
	private:
		//���݂̃V�[��
		ScenePtr currentScene_;
		//�J�ڑO�̃V�[��
		ScenePtr prevScene_;
		//�o�^����Ă���V�[��
		std::unordered_map<SCENE_NO, SceneCreatorPtr> sceneMap_;
		
		//�X�V�^�X�N
		Task::CTaskManager updateTask_;
		//�`��^�X�N
		Task::CTaskManager renderTask_;
		//�QD�`��^�X�N
		Task::CTaskManager render2DTask_;

		//�J�ڃG�t�F�N�g
		SceneChangeEffectPtr changeEffect_;

		//�f�o�b�O�t���O
		bool isDebug_;

		//���݂̃V�[���������t���O
		bool isSceneInit_;

	private:
		/* �v���C�x�[�g�֐� */
		
		//�^�X�N�o�^
		void RegisterTask();
		//�X�V�^�X�N�o�^
		void RegisterUpdateTask();
		//�`��^�X�N�o�^
		void RegisterRenderTask();
		void RegisterRender2DTask();
		//�^�X�N�폜
		void DeleteTask();
		//�f�o�b�O�^�X�N�o�^
		void RegisterDebugTask();
		//�f�o�b�O�^�X�N�폜
		void DeleteDebugTask();
		//�J�ڃG�t�F�N�g�^�X�N�o�^
		void RegisterSceneChangeEffectTask();
		//�J�ڃG�t�F�N�g�^�X�N�폜
		void DeleteSceneChangeEffectTask();
	public:
		CSceneManager();
		~CSceneManager();

		/*
		 * @brief		�V�[���̓o�^
		 * @param		sceneNo	�V�[���ԍ�
		 * @param		creator	�V�[�������N���X
		 */
		void RegistScene(SCENE_NO sceneNo, SceneCreatorPtr creator) override;

		/*
		 * @brief		�V�[���̓o�^
		 * @param		sceneNo	�V�[���ԍ�
		 */
		template < class T >
		void RegistScene(SCENE_NO sceneNo) 
		{
			RegistScene(sceneNo, std::make_unique<SceneCreator<T>>());
		}


		/*
		 * @brief		�V�[���̕ύX
		 * @param		sceneNo	�V�[���ԍ�
		 */
		bool ChangeScene(SCENE_NO sceneNo) override;

		/*
		 * @brief		�V�[���̕ύX
		 * @param		sceneNo	�V�[���ԍ�
		 * @param		sceneNo	�V�[���J�ڃG�t�F�N�g
		 */
		bool ChangeScene(SCENE_NO sceneNo, SceneChangeEffectPtr effect) override;

		/**
		 * @brief		�V�[���ύX(���[�h��ʂ�����)
		 * @param		sceneNo �V�[���ԍ�
		 * @param		sceneNo	�V�[���J�ڃG�t�F�N�g
		 * @param		isLoading ���[�h��ʂ����ނ��H
		 */
		bool ChangeScene(SCENE_NO sceneNo, SceneChangeEffectPtr effect, bool isLoading) override;
		/*
		 * @brief		�V�[���̕ύX�i���[�h�A�������͍s��Ȃ��j
		 * @param		scene	���[�h�ς݂̃V�[��
		 */
		bool ChangeScene(const ScenePtr& scene, SceneChangeEffectPtr effect) override;
		

		/*
		* @brief		���݂̃V�[����������
		* @param		effect	�V�[���ύX���̃G�t�F�N�g
		*/
		void InitializeScene(SceneChangeEffectPtr effect) override;

		/*
		* @brief�@�ǂݍ���
		*/
		bool Load() override;
		/*
		* @brief�@������
		*/
		void Initialize() override;
		/*
		* @brief�@�X�V
		*/
		void Update() override;
		/*
		* @brief�@�`��
		*/
		void Render() override;
		/*
		* @brief�@���
		*/
		void Release() override;

	};

}


