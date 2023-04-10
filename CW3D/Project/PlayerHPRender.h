#pragma once

#include "Common.h"

#include "ResourceManager.h"


namespace ActionGame
{
	/**
	 * @brief		プレイヤーHPUI
	 */
	class CPlayerHPRender
	{
	private:
		//現在の描画HP
		float				currentHP_;
		//現在の描画ゲージ
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
		 * @brief		コンストラクタ
		 */
		CPlayerHPRender();

		/**
		 * @brief		デストラクタ
		 */
		~CPlayerHPRender();
		/*
		* @brief	読み込み
		* @param	trueなら成功
		*/
		bool Load();

		/**
		 * @brief		描画
		 */
		void Render();

		/**
		 * @brief		HP初期化
		 */
		void Reset() noexcept;
		
		/*
		* @brief		解放
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
