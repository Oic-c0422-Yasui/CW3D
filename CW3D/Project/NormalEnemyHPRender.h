#pragma once

#include "EnemyHPRender.h"
#include "ResourceManager.h"

namespace ActionGame
{
	/**
	 * @brief		�GHPUI
	 */
	class NormalEnemyHPRender : public EnemyHPRender
	{
	private:
		
		std::shared_ptr<CSprite3D>			m_pHPBar;
		std::shared_ptr<CSprite3D>			m_pFrame;
		std::shared_ptr<CSprite3D>			m_pDamageBar;

		Vector3 position_;
		Vector3 m_ViewPosition;

		Vector3								offset_;
		Vector3								m_Size;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		NormalEnemyHPRender();

		/**
		 * @brief		�f�X�g���N�^
		 */
		~NormalEnemyHPRender();
		
		bool Load() override;

		/**
		 * @brief		������
		 */
		void Initialize() override;
		/**
		 * @brief		���Z�b�g
		 */
		void Reset() noexcept override;
		/**
		 * @brief		�`��
		 */
		void Render() override;
		/**
		 * @brief		���
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
