#pragma once

#include "Common.h"


namespace ActionGame
{
	/**
	 * @brief		必殺技スキル用フレームUI
	 */
	class CSkillUltGaugeRender
	{
	private:

		std::shared_ptr<CTexture>			availableSkillFrame_;
		std::shared_ptr<CTexture>			unavailableSKillFrame_;
		std::shared_ptr<CTexture>			gaugeFrame_;

		float								gauge_;
		float								maxGauge_;

		Vector2								position_;
		Vector2								gaugePosition_;


	public:
		/**
		 * @brief		コンストラクタ
		 */
		CSkillUltGaugeRender();

		/**
		 * @brief		デストラクタ
		 */
		~CSkillUltGaugeRender();

		/*
		* @brief	読み込み
		* @return	true　なら成功
		*/
		bool Load();

		/*
		* @brief	初期化
		* @param	pos UIの座標
		*/
		void Initialize(const Vector2& pos);

		/*
		* @brief	必殺技ゲージ設定
		* @param	gauge 必殺技ゲージ
		*/
		void SetGauge(float gauge)
		{
			gauge_ = gauge;
		}

		/*
		* @brief	最大必殺技ゲージ設定
		* @param	gauge 最大必殺技ゲージ
		*/
		void SetMaxGauge(float gauge)
		{
			maxGauge_ = gauge;
		}


		/**
		 * @brief		必殺技ゲージ初期化
		 */
		void Reset() noexcept;

		/**
		 * @brief		描画
		 */
		void Render();

		/*
		* @brief		解放
		*/
		void Release();
	};

	using SkillUltGaugeRenderPtr = std::shared_ptr<CSkillUltGaugeRender>;
}
