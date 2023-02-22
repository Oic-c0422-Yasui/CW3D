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

		std::shared_ptr<CTexture>			m_pSKillFrame;
		std::shared_ptr<CTexture>			m_pUsedSKillFrame;
		std::shared_ptr<CTexture>			m_pGaugeFrame;

		float								m_Gauge;
		float								m_MaxGauge;


		Vector2								position_;
		Vector2								m_GaugePosition;


	public:
		/**
		 * @brief		コンストラクタ
		 */
		CSkillUltGaugeRender()
			: m_Gauge(0.0f)
			, m_MaxGauge(0.0f)
			, position_(0, 0)
			, m_GaugePosition(0,0)
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
			m_pSKillFrame = ActionGame::ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "UltFrame");
			m_pUsedSKillFrame = ActionGame::ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "UltFrameMono");
			m_pGaugeFrame = ActionGame::ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "UltSkillGaugeFrame");

		}

		void Initialize(const Vector2& pos)
		{
			position_ = pos;
			//position_.y += m_pSKillFrame->GetHeight() * 0.5f;
			m_GaugePosition = position_ + Vector2(13,-24);
		}


		void SetGauge(float gauge)
		{
			m_Gauge = gauge;
		}

		void SetMaxGauge(float gauge)
		{
			m_MaxGauge = gauge;
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

			float percent = m_Gauge / m_MaxGauge;
			percent = min(percent, 1.0f);
			m_pUsedSKillFrame->Render(position_.x, position_.y, TEXALIGN_BOTTOMCENTER);



			if (percent >= 1.0f)
			{
				m_pSKillFrame->Render(position_.x, position_.y, TEXALIGN_BOTTOMCENTER);
			}

			CRectangle rect(0, m_pGaugeFrame->GetHeight() * (1.0 - percent), m_pGaugeFrame->GetWidth(), m_pGaugeFrame->GetHeight());
			Vector2 pos;
			g_pInput->GetMousePos(pos);
			m_pGaugeFrame->Render(m_GaugePosition.x, m_GaugePosition.y, rect, TEXALIGN_BOTTOMCENTER);
		}

		void Release(void) {
			m_pSKillFrame.reset();
			m_pUsedSKillFrame.reset();
			m_pGaugeFrame.reset();
		}
	};

	using SkillUltGaugeRenderPtr = std::shared_ptr<CSkillUltGaugeRender>;
}
