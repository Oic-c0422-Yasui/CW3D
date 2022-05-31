#pragma once

#include "GameDefine.h"
#include "ResourceManager.h"

namespace Sample
{
	/**
	 * @brief		�v���C���[HPUI
	 */
	class EnemyHPUI
	{
	private:
		//���݂̕`��HP
		float				m_CurrentHP;
		//���݂̕`��Q�[�W
		float				m_CurrentGauge;
		
		std::shared_ptr<CSprite3D>			m_pHPBar;
		std::shared_ptr<CSprite3D>			m_pFrame;

		Vector3								m_Offset;
		Vector3								m_Size;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		EnemyHPUI()
			: m_CurrentHP(1.0f)
			, m_CurrentGauge(1.0f)
		{
			
		}

		/**
		 * @brief		�f�X�g���N�^
		 */
		~EnemyHPUI() {
		}

		void Initialize()
		{
			m_pHPBar = Sample::ResourceManager<CSprite3D>::GetInstance().GetResource("HPBar");
			m_pFrame = Sample::ResourceManager<CSprite3D>::GetInstance().GetResource("HPFrame");
			

			m_pHPBar->m_Angle.x = MOF_MATH_HALFPI;
			m_pFrame->m_Angle.x = MOF_MATH_HALFPI;
			m_Offset = Vector3(0, 2, 0);
			m_Size = Vector3(2, 5, 1);

		}

		/**
		 * @brief		�Ǘ�HP�ݒ�
		 */
		void SetHPGauge(float hp) noexcept {
			m_CurrentHP = hp;
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
		void Render(Vector3 pos) {
			
			m_pFrame->m_Position = pos + m_Offset;
			m_pHPBar->m_Position = pos + m_Offset;
			m_pFrame->m_Scale = m_Size;
			m_pHPBar->m_Scale = m_Size;
			//�l�p��HP�Q�[�W�`��
			m_pFrame->Update();
			
			m_pFrame->Render();
			/*DrawFillBox(72, 12, 572, 36, GetColor(255, 0, 0));*/
			//�\���Q�[�W�����X�ɕω�������
			if (fabsf(m_CurrentGauge - m_CurrentHP) > 0.01f)
			{
				m_CurrentGauge += (m_CurrentHP - m_CurrentGauge) * 0.1f;
				int bright = (int)(74 + 496 * m_CurrentGauge);
				//m_C
				//DrawFillBox(74, 14, bright, 34, GetColor(0, 0, 0));
			}
			else
			{
				m_CurrentGauge = m_CurrentHP;
			}
			int gright = (int)(74 + 496 * m_CurrentHP);
			m_pHPBar->m_Scale.x = m_Size.x *  m_CurrentGauge;
			m_pHPBar->Update();
			m_pHPBar->Render();
			//DrawFillBox(74, 14, gright, 34, GetColor(0, 255, 0));
		}
	};

}
