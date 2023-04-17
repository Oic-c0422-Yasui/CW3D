#pragma once
#include "EnemyHPRender.h"
#include "ResourceManager.h"

namespace ActionGame
{
	/*
	* @brief	�{�XHP�`��
	*/
    class CBossHPRender : public CEnemyHPRender
    {
	private:

		std::shared_ptr<CTexture>			HPBar_;
		std::shared_ptr<CTexture>			HPFrame_;
		std::shared_ptr<CTexture>			damageBar_;

		Vector2 position_;
		Vector2 offset_;

		struct HPBarParam
		{
			const int Limit = 500;
			const BYTE StartColor = 200;
			const BYTE EndColor = 100;
			uint32_t Count;
			uint32_t MaxCount;
			Vector2 CountPos;
		};
		HPBarParam HPBarParam_;

		int HPColor_;

	private:
		/* �v���C�x�[�g�֐��@*/
		//���̐F��ݒ�
		void SettingNextColor();
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CBossHPRender();

		/*
		* @brief	�ǂݍ���
		* @return	true�@�Ȃ琬��
		*/
		bool Load();

		/*
		* @brief	������
		*/
		void Initialize() override;

		/**
		 * @brief		���Z�b�g
		 */
		void Reset() noexcept override;

		/**
		 * @brief		�`��
		 */
		void Render() override;

		/*
		* @brief	���
		*/
		void Release();

    };
	using BossHPRenderPtr = std::shared_ptr<CBossHPRender>;
}


