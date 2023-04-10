#pragma once

#include	"IScene.h"

namespace Scene
{
	/**
	 * @brief		�V�[���ύX�p�C���^�[�t�F�C�X
	 */
	class __declspec(novtable) ISceneChangeEffect
	{
	public:
		/**
		 * @brief		�f�X�g���N�^
		 */
		virtual ~ISceneChangeEffect() = default;

		/**
		 * @brief		�V�[���ύX���ʍX�V
		 */
		virtual void Update() = 0;

		/**
		 * @brief		�V�[���ύX���ʕ`��
		 */
		virtual void Render(const  ScenePtr& prev,
							const  ScenePtr& current) = 0;

		/**
		 * @brief		�V�[���ύX���ʏI������
		 */
		virtual bool IsEnd() const noexcept = 0;

		/*
		* @brief	���Ԃ܂Ői�񂾂��H
		*/
		virtual bool IsHalfPoint() const noexcept = 0;
	};
	using SceneChangeEffectPtr = std::shared_ptr<ISceneChangeEffect>;
}
