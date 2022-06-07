#pragma once

#include "GameDefine.h"
#include	"HPGauge.h"
#include	"HPPosition.h"
#include	"HPShowFlg.h"
#include "ResourceManager.h"

namespace Sample
{
	/**
	 * @brief		プレイヤーHPUI
	 */
	class EnemyHPRender
	{
	private:
		//現在の描画HP
		float				m_CurrentHP;
		//現在の描画ゲージ
		float				m_CurrentGauge;
		
		std::shared_ptr<CSprite3D>			m_pHPBar;
		std::shared_ptr<CSprite3D>			m_pFrame;
		std::shared_ptr<CSprite3D>			m_pDamageBar;

		int m_HP;
		int m_MaxHP;

		Vector3 m_Position;

		bool	m_ShowFlg;

		Vector3								m_Offset;
		Vector3								m_Size;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		EnemyHPRender()
			: m_CurrentHP(1.0f)
			, m_CurrentGauge(1.0f)
			, m_HP(0)
			, m_Position(0,0,0)
			, m_ShowFlg(false)
		{
			
		}

		/**
		 * @brief		デストラクタ
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


		void SetHP(int hp)
		{
			m_HP = hp;
		}

		void SetMaxHP(int hp)
		{
			m_MaxHP = hp;
		}

		bool IsShow()
		{
			return m_ShowFlg;
		}

		void SetPosition(Vector3 pos)
		{
			m_Position = pos;
		}

		void SetShow(bool isShow)
		{
			m_ShowFlg = isShow;
		}

		Vector3 GetPosition()
		{
			return m_Position;
		}

		/**
		 * @brief		管理HP初期化
		 */
		void Reset() noexcept {
			m_CurrentHP = 1.0f;
			m_CurrentGauge = 1.0f;
		}

		/**
		 * @brief		管理スコア初期化
		 */
		void Render() {
			if (!IsShow())
			{
				return;
			}
			m_pFrame->m_Position = m_Position + m_Offset;
			m_pHPBar->m_Position = m_Position + m_Offset;
			m_pDamageBar->m_Position = m_Position + m_Offset;
			
			float parcent = (float)m_HP / (float)m_MaxHP;
			m_CurrentHP = parcent;

			//四角でHPゲージ描画
			m_pFrame->Update();
			
			m_pFrame->Render();
			//表示ゲージを徐々に変化させる
			if (fabsf(m_CurrentGauge - m_CurrentHP) > 0.01f)
			{
				m_CurrentGauge += (m_CurrentHP - m_CurrentGauge) * 0.1f;
				m_pDamageBar->m_Scale.x = m_Size.x * m_CurrentGauge;
				float offset = (m_Size.x - m_pDamageBar->m_Scale.x) * 0.5f;
				m_pDamageBar->m_Position.x = (m_Position.x + m_Offset.x) - offset;
				m_pDamageBar->Update();
				m_pDamageBar->Render();
			}
			else
			{
				m_CurrentGauge = m_CurrentHP;
			}
			m_pHPBar->m_Scale.x = m_Size.x * m_CurrentHP;
			float offset = (m_Size.x - m_pHPBar->m_Scale.x) * 0.5f;
			m_pHPBar->m_Position.x = (m_Position.x + m_Offset.x) - offset;
			m_pHPBar->Update();
			m_pHPBar->Render();
		}

		void Release(void){
			m_pHPBar.reset();
			m_pFrame.reset();
			m_pDamageBar.reset();
		}
	};

	using EnemyHPRenderPtr = std::shared_ptr<EnemyHPRender>;
}
