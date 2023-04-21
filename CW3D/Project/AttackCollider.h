#pragma once

#include "Common.h"

namespace ActionGame
{
	class CAttackCollider
	{
	protected:
		CSphere collider_;

	public:

		CAttackCollider()
			: collider_()

		{
		}

		const CSphere& GetCollider() const noexcept
		{
			return collider_;
		}

		CVector3 GetPosition() const noexcept
		{
			CVector3 pos(0,0,0);
			pos.x = collider_.x;
			pos.y = collider_.y;
			pos.z = collider_.z;

			return pos;
		}

		void SetPosition(const CVector3& pos) noexcept
		{
			collider_.x = pos.x;
			collider_.y = pos.y;
			collider_.z = pos.z;
		}

		void SetPositionX(float x) noexcept
		{
			collider_.x = x;
		}

		void SetPositionY(float y) noexcept
		{
			collider_.y = y;
		}

		void SetPositionZ(float z) noexcept
		{
			collider_.z = z;
		}

		void SetRadius(float radius) noexcept
		{
			collider_.r = radius;
		}


		const float& GetRadius() const noexcept
		{
			return collider_.r;
		}

		void SetCollider(const CSphere& sphere) noexcept
		{
			collider_ = sphere;
		}


	};
	//ポインタ置き換え
	using AttackColliderPtr = std::shared_ptr<CAttackCollider>;
}
