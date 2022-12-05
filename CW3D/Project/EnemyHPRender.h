#pragma once

#include "GameDefine.h"

#include "ResourceManager.h"

namespace ActionGame
{
	/**
	 * @brief		プレイヤーHPUI
	 */
	class CEnemyHPRender
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
		Vector3 m_ViewPosition;

		bool	m_ShowFlg;

		Vector3								m_Offset;
		Vector3								m_Size;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		CEnemyHPRender();

		/**
		 * @brief		デストラクタ
		 */
		~CEnemyHPRender();


		void Initialize();


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

		const Vector3& GetPosition()
		{
			return m_Position;
		}

		/**
		 * @brief		管理HP初期化
		 */
		void Reset() noexcept;

		/**
		 * @brief		HP描画
		 */
		void Render();

		void Release(void);

		const Vector3& GetViewPosition()
		{
			LPCamera cam = CGraphicsUtilities::GetCamera();
			m_ViewPosition = m_Position;
			m_ViewPosition *= cam->GetViewMatrix();
			return m_ViewPosition;
		}
	};

	using EnemyHPRenderPtr = std::shared_ptr<CEnemyHPRender>;
}
