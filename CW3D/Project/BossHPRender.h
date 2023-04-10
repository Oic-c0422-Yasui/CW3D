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
			const int Limit = 100;
			uint32_t Count;
			Vector2 CountPos;
			
			uint32_t CurrentColorId;
			uint32_t NextColorId;
		};
		HPBarParam HPBarParam_;

		MofU32 HPColors_[3];

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


