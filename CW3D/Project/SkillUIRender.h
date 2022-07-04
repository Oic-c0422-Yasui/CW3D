#pragma once

#include "GameDefine.h"
#include "ResourceManager.h"

namespace Sample
{
	/**
	 * @brief		プレイヤーCTUI
	 */
	class SkillUIRender
	{
	private:

		std::shared_ptr<CTexture>			m_pSKillFrame;
		std::shared_ptr<CTexture>			m_pUsedSKillFrame;
		std::shared_ptr<CFont>				m_pFont;

		float								m_CT;
		float								m_MaxCT;

		Vector2								m_Offset;
		Vector2								m_Size;
		Vector2								m_Position;


	public:
		/**
		 * @brief		コンストラクタ
		 */
		SkillUIRender()
			: m_CT(0.0f)
			, m_MaxCT(0.0f)
			, m_Offset(0,0)
			, m_Size(0, 0)
			, m_Position(0, 0)
		{

		}

		/**
		 * @brief		デストラクタ
		 */
		~SkillUIRender() {
		}


		void Load(std::string key)
		{
			m_pSKillFrame = Sample::ResourceManager<CTexture>::GetInstance().GetResource(key);
			m_pUsedSKillFrame = Sample::ResourceManager<CTexture>::GetInstance().GetResource(key + "Mono");
			m_pFont = Sample::ResourceManager<CFont>::GetInstance().GetResource("CTFont");

			m_Offset = Vector2(0, 0);
			m_Size = Vector2(1, 1);
		}

		void Initialize(const Vector2& pos )
		{
			m_Position = pos;
			m_Position.y += m_pSKillFrame->GetHeight() * 0.5f;
		}


		void SetCT(float  ct)
		{
			m_CT = ct;
		}

		void SetMaxCT(float ct)
		{
			m_MaxCT = ct;
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

			float percent = m_CT / m_MaxCT;

			m_pUsedSKillFrame->Render(m_Position.x, m_Position.y, MOF_ARGB(255, 200, 200, 200), TEXALIGN_BOTTOMCENTER);

			CRectangle rect(0, m_pUsedSKillFrame->GetHeight() * percent, m_pUsedSKillFrame->GetWidth(), m_pUsedSKillFrame->GetHeight());
			m_pSKillFrame->Render(m_Position.x, m_Position.y, rect, TEXALIGN_BOTTOMCENTER);

			if (m_CT > 0.0f)
			{
				if (m_CT > 1.0f)
				{
					CRectangle rect;
					m_pFont->CalculateStringRect(0, 0, "0", rect);
					m_pFont->RenderFormatString(m_Position.x - (rect.GetWidth() * 0.5f), m_Position.y - m_pUsedSKillFrame->GetHeight() * 0.5f - (rect.GetHeight() * 0.5f), "%.0f", m_CT);
				}
				else
				{
					CRectangle rect;
					m_pFont->CalculateStringRect(0, 0, "0.0", rect);
					m_pFont->RenderFormatString(m_Position.x - (rect.GetWidth() * 0.5f), m_Position.y - m_pUsedSKillFrame->GetHeight() * 0.5f - (rect.GetHeight() * 0.5f), "%.1f", m_CT);
				}
			}
			
		}

		void Release(void) {
			m_pSKillFrame.reset();
			m_pFont.reset();
		}
	};
	
	using SkillUIRenderPtr = std::shared_ptr<SkillUIRender>;
}
