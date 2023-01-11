#pragma once
#include "EnemyHPRender.h"
#include "ResourceManager.h"

namespace ActionGame
{
    class BossHPRender : public EnemyHPRender
    {
	private:

		std::shared_ptr<CTexture>			m_pHPBar;
		std::shared_ptr<CTexture>			m_pFrame;
		std::shared_ptr<CTexture>			m_pDamageBar;

		Vector2 m_Position;
		Vector2 m_Offset;


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

		Vector2 GetPosition()
		{
			return m_Position;
		}
    };
	using BossHPRenderPtr = std::shared_ptr<BossHPRender>;
}


