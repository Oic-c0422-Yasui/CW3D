#pragma once

#include "Common.h"

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

		Vector2 position_;
		Vector2 offset_;


	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CPlayerHPRender()
			: m_CurrentHP(1.0f)
			, m_CurrentGauge(1.0f)
			, m_HP(0)
			, m_MaxHP(0)
			, position_(0, 0)
			, offset_(0, 0)
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


			position_ = Vector2(763, 1045);
			offset_ = Vector2(58, 1);
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
			return position_;
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

			//g_pInput->GetMousePos(offset_);
			float parcent = (float)m_HP / (float)m_MaxHP;
			parcent = min(parcent, 1.0f);
			m_CurrentHP = parcent;
			//�l�p��HP�Q�[�W�`��
			m_pFrame->Render(position_.x, position_.y);

			//�\���Q�[�W�����X�ɕω�������
			if (fabsf(m_CurrentGauge - m_CurrentHP) > 0.01f)
			{
				m_CurrentGauge += (m_CurrentHP - m_CurrentGauge) * 0.02f;
				CRectangle rect(0, 0, m_pDamageBar->GetWidth() * m_CurrentGauge, m_pDamageBar->GetHeight());
				m_pDamageBar->Render(position_.x + offset_.x,position_.y + offset_.y, rect,MOF_XRGB(218,93,98));
			}
			else
			{
				m_CurrentGauge = m_CurrentHP;
			}
			CRectangle rect(0, 0, m_pHPBar->GetWidth() * m_CurrentHP, m_pHPBar->GetHeight());

			m_pHPBar->Render(position_.x + offset_.x, position_.y + offset_.y, rect);
		}

		void Release(void) {
			m_pHPBar.reset();
			m_pFrame.reset();
			m_pDamageBar.reset();
		}

	};

	using PlayerHPRenderPtr = std::shared_ptr<CPlayerHPRender>;
}
