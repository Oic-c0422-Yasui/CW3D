#pragma once

#include "EnemyHPRender.h"
#include "ResourceManager.h"

namespace ActionGame
{
	/**
	 * @brief		敵HPUI
	 */
	class NormalEnemyHPRender : public EnemyHPRender
	{
	private:
		
		std::shared_ptr<CSprite3D>			m_pHPBar;
		std::shared_ptr<CSprite3D>			m_pFrame;
		std::shared_ptr<CSprite3D>			m_pDamageBar;

		Vector3 m_Position;
		Vector3 m_ViewPosition;

		Vector3								m_Offset;
		Vector3								m_Size;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		NormalEnemyHPRender();

		/**
		 * @brief		デストラクタ
		 */
		~NormalEnemyHPRender();
		
		bool Load() override;

		/**
		 * @brief		初期化
		 */
		void Initialize() override;
		/**
		 * @brief		リセット
		 */
		void Reset() noexcept override;
		/**
		 * @brief		描画
		 */
		void Render() override;
		/**
		 * @brief		解放
		 */
		void Release();



		void SetPosition(Vector3 pos)
		{
			m_Position = pos;
		}


		const Vector3& GetPosition()
		{
			return m_Position;
		}


		const Vector3& GetViewPosition()
		{
			LPCamera cam = CGraphicsUtilities::GetCamera();
			m_ViewPosition = m_Position;
			m_ViewPosition *= cam->GetViewMatrix();
			return m_ViewPosition;
		}
	};

	using NormalEnemyHPRenderPtr = std::shared_ptr<NormalEnemyHPRender>;
}
