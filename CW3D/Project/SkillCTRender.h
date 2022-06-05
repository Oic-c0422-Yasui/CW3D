#pragma once

#include "GameDefine.h"
#include	"CTGauge.h"
#include "ResourceManager.h"

namespace Sample
{
	/**
	 * @brief		プレイヤーCTUI
	 */
	class SkillCTRender
	{
	private:

		std::shared_ptr<CTexture>			m_pSKillFrame;
		std::shared_ptr<CTexture>			m_pUsedSKillFrame;

		CTGaugePtr							m_CT;

		Vector2								m_Offset;
		Vector2								m_Size;
		Vector2								m_Position;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		SkillCTRender(const CTGaugePtr& ct)
			: m_CT(ct)
		{

		}

		/**
		 * @brief		デストラクタ
		 */
		~SkillCTRender() {
		}


		void Initialize(std::string key)
		{
			m_pSKillFrame = Sample::ResourceManager<CTexture>::GetInstance().GetResource(key);
			m_pUsedSKillFrame = Sample::ResourceManager<CTexture>::GetInstance().GetResource(key);

			m_Offset = Vector2(0, 0);
			m_Size = Vector2(1, 1);

		}

		/**
		 * @brief		HPゲージ
		 */
		CTGaugePtr& GetGauge() { return m_CT; }



		/**
		 * @brief		管理HP初期化
		 */
		void Reset() noexcept {

		}

		/**
		 * @brief		管理スコア初期化
		 */
		void Render(float x) {

			m_pUsedSKillFrame->Render(g_pGraphics->GetTargetWidth() * 0.4f + x, g_pGraphics->GetTargetHeight() * 0.9f, MOF_ARGB(255, 10, 10, 10), TEXALIGN_BOTTOMCENTER);

			CRectangle rect(0, m_pUsedSKillFrame->GetHeight() * m_CT->GetPercent(), m_pUsedSKillFrame->GetWidth(), m_pUsedSKillFrame->GetHeight());
			m_pSKillFrame->Render(g_pGraphics->GetTargetWidth() * 0.4f + x, g_pGraphics->GetTargetHeight() * 0.9f, rect, TEXALIGN_BOTTOMCENTER);

			if (m_CT->Get() > 0.0f)
			{
				if (m_CT->Get() > 1.0f)
				{
					CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth() * 0.4f - 5 + x, g_pGraphics->GetTargetHeight() * 0.9f - m_pUsedSKillFrame->GetHeight() * 0.5f, "%.0f", m_CT->Get());
				}
				else
				{
					CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth() * 0.4f - 5 + x, g_pGraphics->GetTargetHeight() * 0.9f - m_pUsedSKillFrame->GetHeight() * 0.5f, "%.1f", m_CT->Get());
				}
			}
			
		}

		void Release(void) {
			m_pSKillFrame.reset();
			m_CT.reset();
		}
	};

}
