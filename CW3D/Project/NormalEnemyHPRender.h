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
		
		std::shared_ptr<CSprite3D>			HPBar_;
		std::shared_ptr<CSprite3D>			HPFrame_;
		std::shared_ptr<CSprite3D>			DamageBar_;

		Vector3 position_;
		Vector3 m_ViewPosition;

		Vector3								offset_;
		Vector3								size_;

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
			position_ = pos;
		}


		const Vector3& GetPosition()
		{
			return position_;
		}


		const Vector3& GetViewPosition()
		{
			LPCamera cam = CGraphicsUtilities::GetCamera();
			m_ViewPosition = position_;
			m_ViewPosition *= cam->GetViewMatrix();
			return m_ViewPosition;
		}
	};

	using NormalEnemyHPRenderPtr = std::shared_ptr<NormalEnemyHPRender>;
}
