#pragma once
#include "Common.h"
#include "ActorObject.h"

namespace Sample
{
	class  CCollision
	{
	private:

		static bool Calculate(const float& boxX, const float& boxY, const float& boxZ, const Vector3& spherePos, const float& sphereR)
		{
			return (boxX - spherePos.x) * (boxX - spherePos.x) +
				(boxY - spherePos.y) * (boxY - spherePos.y) +
				(boxZ - spherePos.z) * (boxZ - spherePos.z) < sphereR * sphereR;
		}

	public:


		//ãÖÇ∆óßï˚ëÃÇ∆ÇÃìñÇΩÇËîªíË
		static bool Collision(const CSphere& sphere, const CAABB& aabb)
		{

			Vector3 boxMin = aabb.Position - aabb.Size;
			Vector3 boxMax = aabb.Position + aabb.Size;
			Vector3 spherePos;
			spherePos.x = sphere.x;
			spherePos.y = sphere.y;
			spherePos.z = sphere.z;
			float r = sphere.r;

			//îÕàÕì‡Ç∆ÇÃîªíË
			if (spherePos.x > boxMin.x && spherePos.x < boxMax.x &&
				spherePos.y > boxMin.y - r && spherePos.y < boxMax.y + r &&
				spherePos.z > boxMin.z && spherePos.z < boxMax.z)
			{
				return true;
			}

			if (spherePos.x > boxMin.x - r && spherePos.x < boxMax.x + r &&
				spherePos.y > boxMin.y && spherePos.y < boxMax.y &&
				spherePos.z > boxMin.z && spherePos.z < boxMax.z)
			{
				return true;
			}

			if (spherePos.x > boxMin.x && spherePos.x < boxMax.x &&
				spherePos.y > boxMin.y && spherePos.y < boxMax.y &&
				spherePos.z > boxMin.z - r && spherePos.z < boxMax.z + r)
			{
				return true;
			}

			//äpÇ∆ÇÃîªíË
			bool result = Calculate(boxMin.x, boxMin.y, boxMin.z, spherePos, r);

			if (result)
			{
				return true;
			}

			result = Calculate(boxMax.x, boxMin.y, boxMin.z, spherePos, r);

			if (result)
			{
				return true;
			}

			result = Calculate(boxMax.x, boxMax.y, boxMin.z, spherePos, r);

			if (result)
			{
				return true;
			}

			result = Calculate(boxMax.x, boxMax.y, boxMax.z, spherePos, r);

			if (result)
			{
				return true;
			}

			result = Calculate(boxMax.x, boxMin.y, boxMax.z, spherePos, r);

			if (result)
			{
				return true;
			}

			result = Calculate(boxMin.x, boxMin.y, boxMax.z, spherePos, r);

			if (result)
			{
				return true;
			}

			result = Calculate(boxMin.x, boxMax.y, boxMax.z, spherePos, r);
			if (result)
			{
				return true;
			}



			return result;
		}

		//ãÖÇ∆ãÖÇ∆ÇÃìñÇΩÇËîªíË
		static bool Collision(CSphere sphere1, CSphere sphere2)
		{
			return sphere1.CollisionSphere(sphere2);
		}

		static bool Collision(CAABB aabb1, CAABB aabb2)
		{
			return aabb1.CollisionAABB(aabb2);
		}

		//ìGÇ∆ìGÇ∆ÇÃìñÇΩÇËîªíË
		static void CollisionActorObject(CActorObject& obj1, CActorObject& obj2)
		{
			if (!obj1.IsShow() || !obj2.IsShow())
			{
				return;
			}
			//ñÑÇ‹ÇËñhé~îªíË
			const Vector3& pos1 = obj1.GetPosition();
			const Vector3& pos2 = obj2.GetPosition();
			const CAABB& size1 = obj1.GetCollider();
			const CAABB& size2 = obj2.GetCollider();
			if (Collision(size1, size2))
			{

				//ç∑ï™ãóó£
				Vector3 sv = pos1 - pos2;
				//Ç®å›Ç¢ÇÃà⁄ìÆÉxÉNÉgÉã
				float ax = fabsf(pos1.x) + fabsf(pos2.x);
				float az = fabsf(pos1.z) + fabsf(pos2.z);
				float ml = ax > az ? ax : az;
				//à⁄ìÆÇµÇƒÇ¢Ç»Ç¢ÇÃÇ…ê⁄êGÅH
				if (ml <= 0)
				{
					//ÇªÇÃèÍçáñÑÇ‹ÇËÇÃäÑçáÇ≈âüÇµèoÇµ
					ax = fabsf(sv.x) / (size1.Size.x + size2.Size.x);
					az = fabsf(sv.z) / (size1.Size.z + size2.Size.z);
					ml = ax > az ? ax : az;
				}
				ax /= ml;
				az /= ml;
				//ñÑÇ‹ÇËñhé~ÇÇ®Ç±Ç»Ç§
				float slx = copysignf((size1.Size.x + size2.Size.x) - (fabsf(sv.x) - 1), sv.x) * ax;
				float slz = copysignf((size1.Size.z + size2.Size.z) - (fabsf(sv.z) - 1), sv.z) * az;
				obj1.SetPosition(pos1 + Vector3(slx * 0.5f, 0.0f, slz * 0.5f));
				obj2.SetPosition(pos2 - Vector3(slx * 0.5f, 0.0f, slz * 0.5f));

			}
		}

		/**
			 * @brief		ìñÇΩÇËîªíËÉeÉìÉvÉåÅ[Égä÷êî
			 */
		template < typename T1, typename T2 >
		static void CollisionObj(T1& obj1, T2& obj2) {
#if _HAS_CXX17
			static_assert("Collision Pair Not Found!!");
#else
			assert(false);
#endif
		}
	};

}




