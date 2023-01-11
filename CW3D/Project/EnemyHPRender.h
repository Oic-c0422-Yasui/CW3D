#pragma once

#include "Common.h"

namespace ActionGame
{
	class EnemyHPRender
	{
	protected:
		//現在の描画HP
		float				m_CurrentHPPercent;
		//現在の描画ゲージ
		float				m_CurrentHPGaugePercent;

		int m_HP;
		int m_MaxHP;

		bool	m_ShowFlg;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		EnemyHPRender();

		/**
		 * @brief		デストラクタ
		 */
		virtual ~EnemyHPRender() = default;


		/**
		 * @brief		読み込み
		 */
		virtual bool Load() = 0;
		/**
		 * @brief		初期化
		 */
		virtual void Initialize() = 0;
		/**
		 * @brief		リセット
		 */
		virtual void Reset() noexcept = 0;

		/**
		 * @brief		描画
		 */
		virtual void Render() = 0;


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

		void SetShow(bool isShow)
		{
			m_ShowFlg = isShow;
		}



	};

	using EnemyHPRenderPtr = std::shared_ptr<EnemyHPRender>;
}


