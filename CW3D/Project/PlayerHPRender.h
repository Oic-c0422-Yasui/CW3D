#pragma once

#include "GameDefine.h"

#include "ResourceManager.h"


namespace ActionGame
{
	/**
	 * @brief		�v���C���[HPUI
	 */
	class CPlayerHPRender
	{
	private:
		//���݂̕`��HP
		float				m_CurrentHP;
		//���݂̕`��Q�[�W
		float				m_CurrentGauge;

		std::shared_ptr<CTexture>			m_pHPBar;
		std::shared_ptr<CTexture>			m_pFrame;
		std::shared_ptr<CTexture>			m_pDamageBar;

		int m_HP;
		int m_MaxHP;

		Vector2 m_Position;
		Vector2 m_Offset;


	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CPlayerHPRender()
			: m_CurrentHP(1.0f)
			, m_CurrentGauge(1.0f)
			, m_HP(0)
			, m_MaxHP(0)
			, m_Position(0, 0)
			, m_Offset(0, 0)
		{
			
		}

		/**
		 * @brief		�f�X�g���N�^
		 */
		~CPlayerHPRender() {
		}


		void Load()
		{
			m_pHPBar = ActionGame::ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "PlayerHPBar");
			m_pFrame = ActionGame::ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "PlayerHPFrame");
			m_pDamageBar = ActionGame::ResourcePtrManager<CTexture>::GetInstance().GetResource("UI", "PlayerHPBar");


			m_Position = Vector2(763, 1045);
			m_Offset = Vector2(58, 1);
		}

		void SetHP(int hp)
		{
			m_HP = hp;
		}

		void SetMaxHP(int hp)
		{
			m_MaxHP = hp;
		}


		Vector2 GetPosition()
		{
			return m_Position;
		}

		/**
		 * @brief		�Ǘ�HP������
		 */
		void Reset() noexcept {
			m_CurrentHP = 1.0f;
			m_CurrentGauge = 1.0f;
		}

		/**
		 * @brief		�Ǘ��X�R�A������
		 */
		void Render() {

			//g_pInput->GetMousePos(m_Offset);
			float parcent = (float)m_HP / (float)m_MaxHP;
			parcent = min(parcent, 1.0f);
			m_CurrentHP = parcent;
			//�l�p��HP�Q�[�W�`��
			m_pFrame->Render(m_Position.x, m_Position.y);

			//�\���Q�[�W�����X�ɕω�������
			if (fabsf(m_CurrentGauge - m_CurrentHP) > 0.01f)
			{
				m_CurrentGauge += (m_CurrentHP - m_CurrentGauge) * 0.02f;
				CRectangle rect(0, 0, m_pDamageBar->GetWidth() * m_CurrentGauge, m_pDamageBar->GetHeight());
				m_pDamageBar->Render(m_Position.x + m_Offset.x,m_Position.y + m_Offset.y, rect,MOF_XRGB(218,93,98));
			}
			else
			{
				m_CurrentGauge = m_CurrentHP;
			}
			CRectangle rect(0, 0, m_pHPBar->GetWidth() * m_CurrentHP, m_pHPBar->GetHeight());

			m_pHPBar->Render(m_Position.x + m_Offset.x, m_Position.y + m_Offset.y, rect);
		}

		void Release(void) {
			m_pHPBar.reset();
			m_pFrame.reset();
			m_pDamageBar.reset();
		}

	};

	using PlayerHPRenderPtr = std::shared_ptr<CPlayerHPRender>;
}
