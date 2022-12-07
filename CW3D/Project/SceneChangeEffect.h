#pragma once

#include	"SceneBase.h"

namespace ActionGame
{
	/**
	 * @brief		�V�[���ύX�p���ʃC���^�[�t�F�C�X
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
		virtual void Render(ScenePtr& prev,
						ScenePtr& current) = 0;

		/**
		 * @brief		�V�[���ύX���ʏI������
		 */
		virtual bool IsEnd() const noexcept = 0;
	};
	using SceneChangeEffectPtr = std::shared_ptr<ISceneChangeEffect>;
}
