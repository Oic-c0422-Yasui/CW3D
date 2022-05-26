#pragma once

#include "Common.h"

namespace Sample
{
	class CAttackCollider
	{
	protected:
		CSphere m_Collision;

	public:

		CAttackCollider()
			: m_Collision()

		{
		}

		const CSphere& GetCollider() const noexcept
		{
			return m_Collision;
		}

		CVector3 GetPosition() const noexcept
		{
			CVector3 pos(0,0,0);
			pos.x = m_Collision.x;
			pos.y = m_Collision.y;
			pos.z = m_Collision.z;

			return pos;
		}

		void SetPosition(const CVector3& pos) noexcept
		{
			m_Collision.x = pos.x;
			m_Collision.y = pos.y;
			m_Collision.z = pos.z;
		}

		void SetPositionX(const float& x) noexcept
		{
			m_Collision.x = x;
		}

		void SetPositionY(const float& y) noexcept
		{
			m_Collision.y = y;
		}

		void SetPositionZ(const float& z) noexcept
		{
			m_Collision.z = z;
		}

		void SetRadius(const float& radius) noexcept
		{
			m_Collision.r = radius;
		}


		const float& GetRadius() const noexcept
		{
			return m_Collision.r;
		}

		void SetCollider(const CSphere& sphere) noexcept
		{
			m_Collision = sphere;
		}


	};
	//ポインタ置き換え
	using AttackColliderPtr = std::shared_ptr<CAttackCollider>;
}
