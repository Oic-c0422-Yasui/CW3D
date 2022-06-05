#pragma once

#include "GameDefine.h"
#include	"HPGauge.h"
#include	"HPPosition.h"
#include	"HPShowFlg.h"
#include "ResourceManager.h"

namespace Sample
{
	/**
	 * @brief		�v���C���[HPUI
	 */
	class EnemyHPRender
	{
	private:
		//���݂̕`��HP
		float				m_CurrentHP;
		//���݂̕`��Q�[�W
		float				m_CurrentGauge;
		
		std::shared_ptr<CSprite3D>			m_pHPBar;
		std::shared_ptr<CSprite3D>			m_pFrame;
		std::shared_ptr<CSprite3D>			m_pDamageBar;

		HPGaugePtr							m_HP;
		HPPositionPtr						m_Position;
		HPShowFlgPtr						m_ShowFlg;

		Vector3								m_Offset;
		Vector3								m_Size;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		EnemyHPRender(const HPGaugePtr& hp,const HPPositionPtr& pos, const HPShowFlgPtr& isShow)
			: m_CurrentHP(1.0f)
			, m_CurrentGauge(1.0f)
			, m_HP(hp)
			, m_Position(pos)
			, m_ShowFlg(isShow)
		{
			
		}

		/**
		 * @brief		�f�X�g���N�^
		 */
		~EnemyHPRender() {
		}


		void Initialize()
		{
			m_pHPBar = Sample::ResourceManager<CSprite3D>::GetInstance().GetResource("HPBar");
			m_pFrame = Sample::ResourceManager<CSprite3D>::GetInstance().GetResource("HPFrame");
			m_pDamageBar = Sample::ResourceManager<CSprite3D>::GetInstance().GetResource("DamageBar");
			

			m_Offset = Vector3(0, 2, 0);
			m_Size = Vector3(1, 0.8f, 1);
			m_pHPBar->m_Angle.z = MOF_ToRadian(180);
			m_pFrame->m_Angle.z = MOF_ToRadian(180);
			m_pDamageBar->m_Angle.z = MOF_ToRadian(180);
			m_pHPBar->m_Angle.x = MOF_ToRadian(0);
			m_pFrame->m_Angle.x = MOF_ToRadian(0);
			m_pDamageBar->m_Angle.x = MOF_ToRadian(0);
			m_pFrame->m_Scale = m_Size;
			m_pHPBar->m_Scale = m_Size;
			m_pDamageBar->m_Scale = m_Size;
			m_pFrame->m_Color = CVector4(1.0f, 1.0f, 1.0f, 0.75f);

		}

		/**
		 * @brief		HP�Q�[�W
		 */
		HPGaugePtr& GetGauge() { return m_HP; }

		HPPositionPtr& GetHPPositonPtr() { return m_Position; }

		HPShowFlgPtr& GetHPShowFlgPtr() { return m_ShowFlg; }

		bool IsShow()
		{
			return m_ShowFlg->Get();
		}

		Vector3 GetPosition()
		{
			return m_Position->Get();
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
			if (!IsShow())
			{
				return;
			}
			m_pFrame->m_Position = m_Position->Get() + m_Offset;
			m_pHPBar->m_Position = m_Position->Get() + m_Offset;
			m_pDamageBar->m_Position = m_Position->Get() + m_Offset;
			
			m_CurrentHP = m_HP->GetPercent();

			//�l�p��HP�Q�[�W�`��
			m_pFrame->Update();
			
			m_pFrame->Render();
			//�\���Q�[�W�����X�ɕω�������
			if (fabsf(m_CurrentGauge - m_CurrentHP) > 0.01f)
			{
				m_CurrentGauge += (m_CurrentHP - m_CurrentGauge) * 0.1f;
				m_pDamageBar->m_Scale.x = m_Size.x * m_CurrentGauge;
				float offset = (m_Size.x - m_pDamageBar->m_Scale.x) * 0.5f;
				m_pDamageBar->m_Position.x = (m_Position->Get().x + m_Offset.x) - offset;
				m_pDamageBar->Update();
				m_pDamageBar->Render();
			}
			else
			{
				m_CurrentGauge = m_CurrentHP;
			}
			m_pHPBar->m_Scale.x = m_Size.x * m_CurrentHP;
			float offset = (m_Size.x - m_pHPBar->m_Scale.x) * 0.5f;
			m_pHPBar->m_Position.x = (m_Position->Get().x + m_Offset.x) - offset;
			m_pHPBar->Update();
			m_pHPBar->Render();
		}

		void Release(void){
			m_pHPBar.reset();
			m_pFrame.reset();
			m_pDamageBar.reset();
			m_HP.reset();
			m_Position.reset();
			m_ShowFlg.reset();
		}
	};

}
