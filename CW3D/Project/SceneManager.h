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
	class SceneManager : public ISceneManager
	{
	private:

		ScenePtr scene_;
		std::unordered_map<SCENENO, SceneCreatorPtr> sceneMap_;
		Task::CTaskManager updateTask_;
		Task::CTaskManager renderTask_;
		Task::CTaskManager render2DTask_;

		SceneChangeEffectPtr sceneEffect_;

		bool isDebug_;

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
		SceneManager();
		~SceneManager();

		/*
		 * @brief		�V�[���̓o�^
		 * @param		sceneNo	�V�[���ԍ�
		 * @param		creator	�V�[�������N���X
		 */
		void RegistScene(SCENENO sceneNo, SceneCreatorPtr creator) override;

		/*
		 * @brief		�V�[���̓o�^
		 * @param		sceneNo	�V�[���ԍ�
		 */
		template < class T >
		void RegistScene(SCENENO sceneNo) 
		{
			RegistScene(sceneNo, std::make_unique<SceneCreator<T>>());
		}


		/*
		 * @brief		�V�[���̕ύX
		 * @param		sceneNo	�V�[���ԍ�
		 */
		bool ChangeScene(SCENENO sceneNo) override;

		/**
		 * @brief		�V�[���ύX(���[�h��ʂ�����)
		 * @param		sceneNo �V�[���ԍ�
		 * @param		isLoading ���[�h��ʂ����ނ��H
		 */
		bool ChangeScene(SCENENO sceneNo,bool isLoading) override;
		/*
		 * @brief		�V�[���̕ύX�i���[�h�A�������͍s��Ȃ��j
		 * @param		scene	���[�h�ς݂̃V�[��
		 */
		bool ChangeScene(const ScenePtr& scene) override;
		

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


