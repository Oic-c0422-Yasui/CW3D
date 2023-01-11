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
		 * @brief		コンストラクタ
		 */
		BossHPRender();


		bool Load();

		void Initialize() override;


		/**
		 * @brief		リセット
		 */
		void Reset() noexcept override;

		/**
		 * @brief		管理スコア初期化
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


