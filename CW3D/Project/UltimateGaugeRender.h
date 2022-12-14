#pragma once
#pragma once

#include "Common.h"
#include "ResourceManager.h"

namespace ActionGame
{
	/**
	 * @brief		�K�E�Z�Q�[�W
	 */
	class CUltimateGaugeRender
	{
	private:

		std::shared_ptr<CTexture>			m_pGaugeFrame;

		std::shared_ptr<CFont>				m_pFont;

		float								m_Gauge;
		float								m_MaxGauge;

		Vector2								m_Offset;
		Vector2								m_Size;
		Vector2								m_Position;

		Vector2								m_FontPosition;


	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CUltimateGaugeRender()
			: m_Gauge(0.2f)
			, m_MaxGauge(1.0f)
			, m_Offset(0, 0)
			, m_Size(0, 0)
			, m_Position(0, 0)
		{

		}

		/**
		 * @brief		�f�X�g���N�^
		 */
		~CUltimateGaugeRender() {
		}


		void Load()
		{

			m_pGaugeFrame = ActionGame::ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "UltGauge");
			m_pFont = ActionGame::ResourcePtrManager<CFont>::GetInstance().GetResource("Font", "SkillFont");

			m_Offset = Vector2(0, 0);
			m_Size = Vector2(1, 1);
			m_Position = Vector2(634, 1052);

			//�t�H���g���W
			CRectangle fontrect;
			m_pFont->CalculateStringRect(0, 0, "000/000", fontrect);
			m_FontPosition = Vector2(m_Position.x - (fontrect.GetWidth() * 0.5f), m_Position.y - m_pGaugeFrame->GetHeight() * 0.5f - (fontrect.GetHeight() * 0.5f));
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
		 * @brief		�Ǘ�HP������
		 */
		void Reset() noexcept {

		}

		/**
		 * @brief		�Ǘ��X�R�A������
		 */
		void Render() {

			float percent = m_Gauge / m_MaxGauge;

			CRectangle rect(0, m_pGaugeFrame->GetHeight() * (1.0 - percent), m_pGaugeFrame->GetWidth(), m_pGaugeFrame->GetHeight());
			m_pGaugeFrame->Render(m_Position.x, m_Position.y,rect, TEXALIGN_BOTTOMCENTER);

			m_pFont->RenderFormatString(m_FontPosition.x, m_FontPosition.y, "%03.0f/%03.0f", m_Gauge,m_MaxGauge);

		}

		void Release(void) {
			m_pGaugeFrame.reset();
			m_pFont.reset();
		}
	};

	using UltimateGaugeUIRenderPtr = std::shared_ptr<CUltimateGaugeRender>;
}
