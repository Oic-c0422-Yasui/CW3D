#pragma once

#include "GameDefine.h"
#include "ResourceManager.h"

namespace Sample
{
	/**
	 * @brief		プレイヤーCTUI
	 */
	class CSkillRender
	{
	protected:

		std::shared_ptr<CTexture>			m_pSKillFrame;
		std::shared_ptr<CTexture>			m_pUsedSKillFrame;
		std::shared_ptr<CFont>				m_pFont;

		float								m_CT;
		float								m_MaxCT;
		bool								m_CanUseFlg;

		Vector2								m_Offset;
		Vector2								m_Size;
		Vector2								m_Position;


	public:
		/**
		 * @brief		コンストラクタ
		 */
		CSkillRender()
			: m_CT(0.0f)
			, m_MaxCT(0.0f)
			, m_Offset(0,0)
			, m_Size(0, 0)
			, m_Position(0, 0)
			, m_CanUseFlg(false)
		{

		}

		/**
		 * @brief		デストラクタ
		 */
		virtual ~CSkillRender() {
			Release();
		}


		virtual void Load(const std::string& key)
		{
			m_pSKillFrame = Sample::ResourcePtrManager<CTexture>::GetInstance().GetResource(key);
			m_pUsedSKillFrame = Sample::ResourcePtrManager<CTexture>::GetInstance().GetResource(key + "Mono");
			m_pFont = Sample::ResourcePtrManager<CFont>::GetInstance().GetResource("CTFont");

			m_Offset = Vector2(0, 0);
			m_Size = Vector2(1, 1);
		}

		virtual void Initialize(const Vector2& pos )
		{
			m_Position = pos;
			m_Position.y += m_pSKillFrame->GetHeight() * 0.5f;
		}


		const Vector2& GetPosition()
		{
			return m_Position;
		}

		void SetCT(float  ct)
		{
			m_CT = ct;
		}

		void SetMaxCT(float ct)
		{
			m_MaxCT = ct;
		}

		void SetCanUseFlg(bool canUse)
		{
			m_CanUseFlg = canUse;
		}

		/**
		 * @brief		管理HP初期化
		 */
		void Reset() noexcept {

		}

		/**
		 * @brief		管理スコア初期化
		 */
		virtual void Render() {

			float percent = m_CT / m_MaxCT;
			percent = min(percent, 1.0f);
			m_pUsedSKillFrame->Render(m_Position.x, m_Position.y, MOF_ARGB(255, 128, 128, 128), TEXALIGN_BOTTOMCENTER);
			CRectangle rect(0, m_pUsedSKillFrame->GetHeight() * percent, m_pUsedSKillFrame->GetWidth(), m_pUsedSKillFrame->GetHeight());
			m_pUsedSKillFrame->Render(m_Position.x, m_Position.y, rect, TEXALIGN_BOTTOMCENTER);

			if (m_CanUseFlg)
			{
				m_pSKillFrame->Render(m_Position.x, m_Position.y, TEXALIGN_BOTTOMCENTER);
			}

			
			RenderStrCT(m_CT);
		}


		void RenderStrCT(float ct)
		{
			if (ct <= 0.0f)
			{
				return;
			}

			if (ct > 1.0f)
			{
				CRectangle rect;
				m_pFont->CalculateStringRect(0, 0, "0", rect);
				m_pFont->RenderFormatString(m_Position.x - (rect.GetWidth() * 0.5f), m_Position.y - m_pUsedSKillFrame->GetHeight() * 0.5f - (rect.GetHeight() * 0.5f), "%.0f", ct);
			}
			else
			{
				CRectangle rect;
				m_pFont->CalculateStringRect(0, 0, "0.0", rect);
				m_pFont->RenderFormatString(m_Position.x - (rect.GetWidth() * 0.5f), m_Position.y - m_pUsedSKillFrame->GetHeight() * 0.5f - (rect.GetHeight() * 0.5f), "%.1f", ct);
			}
		}

		virtual void Release(void) {
			m_pSKillFrame.reset();
			m_pFont.reset();
		}
	};
	
	using SkillRenderPtr = std::shared_ptr<CSkillRender>;
}
