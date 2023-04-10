#pragma once

#include "Common.h"

namespace ActionGame
{
	class CEnemyHPRender
	{
	protected:
		//現在の描画HP
		float				currentHPPercent_;
		//現在の描画ゲージ
		float				currentHPGaugePercent_;

		int HP_;
		int maxHP_;

		bool	isShow_;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		CEnemyHPRender();

		/**
		 * @brief		デストラクタ
		 */
		virtual ~CEnemyHPRender() = default;


		/**
		 * @brief		読み込み
		 */
		virtual bool Load() = 0;
		/**
		 * @brief		初期化
		 */
		virtual void Initialize() = 0;
		/**
		 * @brief		リセット
		 */
		virtual void Reset() noexcept = 0;

		/**
		 * @brief		描画
		 */
		virtual void Render() = 0;


		virtual void SetHP(int hp)
		{
			HP_ = hp;
		}

		virtual void SetMaxHP(int hp)
		{
			maxHP_ = hp;
		}

		bool IsShow()
		{
			return isShow_;
		}

		void SetShow(bool isShow)
		{
			isShow_ = isShow;
		}

	};

	using EnemyHPRenderPtr = std::shared_ptr<CEnemyHPRender>;
}


