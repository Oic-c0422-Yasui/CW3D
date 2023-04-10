#pragma once

#include "EnemyHPRender.h"
#include "ResourceManager.h"

namespace ActionGame
{
	/**
	 * @brief		�GHPUI
	 */
	class CNormalEnemyHPRender : public CEnemyHPRender
	{
	private:
		
		std::shared_ptr<CSprite3D>			HPBar_;
		std::shared_ptr<CSprite3D>			HPFrame_;
		std::shared_ptr<CSprite3D>			damageBar_;

		Vector3								position_;
		Vector3								viewPosition_;

		Vector3								offset_;
		Vector3								size_;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		CNormalEnemyHPRender();

		/**
		 * @brief		�f�X�g���N�^
		 */
		~CNormalEnemyHPRender();
		
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
			viewPosition_ = position_;
			viewPosition_ *= cam->GetViewMatrix();
			return viewPosition_;
		}
	};

	using NormalEnemyHPRenderPtr = std::shared_ptr<CNormalEnemyHPRender>;
}
