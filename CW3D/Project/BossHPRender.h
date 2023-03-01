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
		/* プライベート関数　*/
		void SettingNextColor();
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

    };
	using BossHPRenderPtr = std::shared_ptr<BossHPRender>;
}


