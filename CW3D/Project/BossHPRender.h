#pragma once
#include "EnemyHPRender.h"
#include "ResourceManager.h"

namespace ActionGame
{
    class BossHPRender : public EnemyHPRender
    {
	private:

		std::shared_ptr<CTexture>			HPBar_;
		std::shared_ptr<CTexture>			HPFrame_;
		std::shared_ptr<CTexture>			DamageBar_;

		Vector2 position_;
		Vector2 offset_;

		struct HPBar
		{
			const int Limit = 100;
			size_t Count;
			Vector2 CountPos;
			
			size_t CurrentColorId;
			size_t NextColorId;
		};

		HPBar m_HPBar;

		MofU32 m_HPColors[3];

	private:
		/* �v���C�x�[�g�֐��@*/
		void SettingNextColor();
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		BossHPRender();


		bool Load();

		void Initialize() override;


		/**
		 * @brief		���Z�b�g
		 */
		void Reset() noexcept override;

		/**
		 * @brief		�Ǘ��X�R�A������
		 */
		void Render() override;

		void Release();

    };
	using BossHPRenderPtr = std::shared_ptr<BossHPRender>;
}


