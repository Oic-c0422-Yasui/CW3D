#pragma once
#include	"SceneRegister.h"
#include	"SceneChanger.h"
#include	"SceneInitializer.h"
#include	"SceneChangeEffect.h"


namespace ActionGame
{
	/*
	* �V�[���Ǘ��p�C���^�t�F�[�X
	*/
	class  ISceneManager : public ISceneChanger, public ISceneRegister, public ISceneInitializer
	{
	public:
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~ISceneManager() = default;

		/**
		 * @brief		�ǂݍ���
		 */
		virtual bool Load() = 0;

		/**
		 * @brief		������
		 */
		virtual void Initialize() = 0;

		/**
		 * @brief		�X�V
		 */
		virtual void Update() = 0;

		/**
		 * @brief		�`��
		 */
		virtual void Render() = 0;

		/**
		 * @brief		���
		 */
		virtual void Release() = 0;
	};

	using SceneManagerPtr = std::shared_ptr<ISceneManager>;
}

