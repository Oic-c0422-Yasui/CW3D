#pragma once

#include	"SceneBase.h"
#include "GameDefine.h"

namespace ActionGame
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
		 */
		virtual bool ChangeScene(tag_SCENENO sceneNo) = 0;


		/**
		 * @brief		�V�[���ύX(���[�h��ʂ�����)
		 * @param		sceneNo �V�[���ԍ�
		 * @param		isLoading ���[�h��ʂ����ނ��H
		 */
		virtual bool ChangeScene(tag_SCENENO sceneNo,bool isLoading) = 0;
		
		/**
		 * @brief		�V�[���ύX
		 */
		virtual bool ChangeScene(const ScenePtr& scene) = 0;

	};
	using SceneChangerPtr = std::shared_ptr<ISceneChanger>;
}


