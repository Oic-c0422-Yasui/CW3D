#pragma once
#include "ISceneManager.h"
#include "SceneCreator.h"
#include <unordered_map>
#include "ThreadCreator.h"
#include "TaskManager.h"

namespace ActionGame
{
	/**
	 * �V�[���}�l�[�W���[
	 */
	class SceneManager : public ISceneManager
	{
	private:

		ScenePtr m_Scene;

		std::unordered_map<tag_SCENENO, SceneCreatorPtr> m_SceneMap;

		TaskManager m_UpdateTask;

		bool m_DebugFlg;

	private:
		/* //�v���C�x�[�g�֐� */
		
		//�^�X�N�o�^
		void RegisterTask();
		//�X�V�^�X�N�o�^
		void RegisterUpdateTask();
		//�f�o�b�O�^�X�N�o�^
		void RegisterDebugTask();
		//�f�o�b�O�^�X�N�폜
		void DeleteDebugTask();

	public:
		SceneManager();
		~SceneManager();

		/*
		 * @brief		�V�[���̓o�^
		 */
		void RegistScene(tag_SCENENO sceneNo, SceneCreatorPtr creator) override;

		/*
		 * @brief		�V�[���̓o�^
		 */
		template < class T >
		void RegistScene(tag_SCENENO sceneNo) 
		{
			RegistScene(sceneNo, std::make_unique<SceneCreator<T>>());
		}


		/*
		 * @brief		�V�[���̕ύX
		 */
		bool ChangeScene(tag_SCENENO sceneNo) override;
		/**
		 * @brief		�V�[���ύX(���[�h��ʂ�����)
		 * @param		sceneNo �V�[���ԍ�
		 * @param		isLoading ���[�h��ʂ����ނ��H
		 */
		bool ChangeScene(tag_SCENENO sceneNo,bool isLoading) override;
		/*
		 * @brief		�V�[���̕ύX
		 */
		bool ChangeScene(const ScenePtr& scene) override;
		

		/*
		* @brief		���݂̃V�[����������
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


