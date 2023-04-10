#pragma once

#include "Common.h"

#include "ResourceManager.h"


namespace ActionGame
{
	/**
	 * @brief		�v���C���[HPUI
	 */
	class CPlayerHPRender
	{
	private:
		//���݂̕`��HP
		float				currentHP_;
		//���݂̕`��Q�[�W
		float				currentGauge_;

		std::shared_ptr<CTexture>			HPBar_;
		std::shared_ptr<CTexture>			HPFrame_;
		std::shared_ptr<CTexture>			damageBar_;

		int HP_;
		int maxHP_;

		Vector2 position_;
		Vector2 offset_;


	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CPlayerHPRender();

		/**
		 * @brief		�f�X�g���N�^
		 */
		~CPlayerHPRender();
		/*
		* @brief	�ǂݍ���
		* @param	true�Ȃ琬��
		*/
		bool Load();

		/**
		 * @brief		�`��
		 */
		void Render();

		/**
		 * @brief		HP������
		 */
		void Reset() noexcept;
		
		/*
		* @brief		���
		*/
		void Release();

		void SetHP(int hp)
		{
			HP_ = hp;
		}

		void SetMaxHP(int hp)
		{
			maxHP_ = hp;
		}

	};

	using PlayerHPRenderPtr = std::shared_ptr<CPlayerHPRender>;
}
