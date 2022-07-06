#pragma once

#include "GameDefine.h"
#include "ResourceManager.h"
#include "SkillRender.h"

namespace Sample
{
	/**
	 * @brief		プレイヤーCTUI
	 */
	class CAdditionalSkillRender : public CSkillRender
	{
	private:
		float m_AddCT;
		float m_AddMaxCT;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		CAdditionalSkillRender()
			: CSkillRender()
			, m_AddCT(0.0f)
			, m_AddMaxCT(0.0f)
		{

		}

		/**
		 * @brief		デストラクタ
		 */
		~CAdditionalSkillRender() {
			Release();
		}

		void SetAddCT(float ct)
		{
			m_AddCT = ct;
		}

		void SetAddMaxCT(float ct)
		{
			m_AddMaxCT = ct;
		}

		void Load(const std::string& key)
		{
			CSkillRender::Load(key);

		}

		void Initialize(const Vector2& pos)
		{
			CSkillRender::Initialize(pos);
		}


		/**
		 * @brief		管理スコア初期化
		 */
		void Render() {

			float percent = m_CT / m_MaxCT;

			m_pUsedSKillFrame->Render(m_Position.x, m_Position.y, MOF_ARGB(255, 128, 128, 128), TEXALIGN_BOTTOMCENTER);
			CRectangle rect(0, m_pUsedSKillFrame->GetHeight() * percent, m_pUsedSKillFrame->GetWidth(), m_pUsedSKillFrame->GetHeight());
			m_pUsedSKillFrame->Render(m_Position.x, m_Position.y, rect, TEXALIGN_BOTTOMCENTER);

			RenderStrCT(m_AddCT);

			if (m_CanUseFlg)
			{
				m_pSKillFrame->Render(m_Position.x, m_Position.y, TEXALIGN_BOTTOMCENTER);
			}

			RenderStrCT(m_CT);

		}

		void Release(void) {
			m_pSKillFrame.reset();
			m_pFont.reset();
		}
	};

	using AdditionalSkillRenderPtr = std::shared_ptr<CAdditionalSkillRender>;
}
