#pragma once

#include "Common.h"


namespace ActionGame
{
	/**
	 * @brief		必殺技ゲージUI
	 */
	class CUltimateGaugeRender
	{
	private:

		std::shared_ptr<CTexture>			gaugeBar_;
		std::shared_ptr<CTexture>			gaugeFrame_;


		std::shared_ptr<CFont>				font_;

		float								gauge_;
		float								maxGauge_;

		Vector2								offset_;
		Vector2								size_;
		Vector2								position_;

		Vector2								strPosition_;


	public:
		/**
		 * @brief		コンストラクタ
		 */
		CUltimateGaugeRender();


		/**
		 * @brief		デストラクタ
		 */
		~CUltimateGaugeRender();

		/**
		 * @brief		読み込み
		 * @return		trueなら成功
		 */
		bool Load();
		/**
		 * @brief		描画
		 */
		void Render();
		/**
		 * @brief		解放
		 */
		void Release();


		void SetGauge(float gauge)
		{
			gauge_ = gauge;
		}

		void SetMaxGauge(float gauge)
		{
			maxGauge_ = gauge;
		}

	};

	using UltimateGaugeUIRenderPtr = std::shared_ptr<CUltimateGaugeRender>;
}
