#pragma once

#include "Common.h"
#include "ResourceManager.h"

namespace ActionGame
{
	/**
	 * @brief		プレイヤーCTUI
	 */
	class CSkillUltGaugeRender
	{
	private:

		std::shared_ptr<CTexture>			sKillFrame_;
		std::shared_ptr<CTexture>			usedSKillFrame_;
		std::shared_ptr<CTexture>			gaugeFrame_;

		float								gauge_;
		float								maxGauge_;


		Vector2								position_;
		Vector2								gaugePosition_;


	public:
		/**
		 * @brief		コンストラクタ
		 */
		CSkillUltGaugeRender()
			: gauge_(0.0f)
			, maxGauge_(0.0f)
			, position_(0, 0)
			, gaugePosition_(0,0)
		{

		}

		/**
		 * @brief		デストラクタ
		 */
		~CSkillUltGaugeRender() {
			Release();
		}


		void Load()
		{
			sKillFrame_ = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "UltFrame");
			usedSKillFrame_ = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "UltFrameMono");
			gaugeFrame_ = ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "UltSkillGaugeFrame");

		}

		void Initialize(const Vector2& pos)
		{
			position_ = pos;
			//position_.y += sKillFrame_->GetHeight() * 0.5f;
			gaugePosition_ = position_ + Vector2(13,-24);
		}


		void SetGauge(float gauge)
		{
			gauge_ = gauge;
		}

		void SetMaxGauge(float gauge)
		{
			maxGauge_ = gauge;
		}


		/**
		 * @brief		管理HP初期化
		 */
		void Reset() noexcept {

		}

		/**
		 * @brief		管理スコア初期化
		 */
		void Render() {

			float percent = gauge_ / maxGauge_;
			percent = min(percent, 1.0f);
			usedSKillFrame_->Render(position_.x, position_.y, TEXALIGN_BOTTOMCENTER);



			if (percent >= 1.0f)
			{
				sKillFrame_->Render(position_.x, position_.y, TEXALIGN_BOTTOMCENTER);
			}

			CRectangle rect(0, gaugeFrame_->GetHeight() * (1.0 - percent), gaugeFrame_->GetWidth(), gaugeFrame_->GetHeight());
			Vector2 pos;
			g_pInput->GetMousePos(pos);
			gaugeFrame_->Render(gaugePosition_.x, gaugePosition_.y, rect, TEXALIGN_BOTTOMCENTER);
		}

		void Release(void) {
			sKillFrame_.reset();
			usedSKillFrame_.reset();
			gaugeFrame_.reset();
		}
	};

	using SkillUltGaugeRenderPtr = std::shared_ptr<CSkillUltGaugeRender>;
}
