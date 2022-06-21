#pragma once
#include "Common.h"
#include "ActorObject.h"

namespace Sample
{
	class  CCollision
	{
	private:

		static bool Calculate(const float boxX, const float boxY, const float boxZ, const Vector3& spherePos, const float sphereR)
		{
			return (boxX - spherePos.x) * (boxX - spherePos.x) +
				(boxY - spherePos.y) * (boxY - spherePos.y) +
				(boxZ - spherePos.z) * (boxZ - spherePos.z) < sphereR * sphereR;
		}

	public:


		//球と立方体との当たり判定
		static bool Collision(const CSphere& sphere, const CAABB& aabb)
		{

			Vector3 boxMin = aabb.Position - aabb.Size;
			Vector3 boxMax = aabb.Position + aabb.Size;
			Vector3 spherePos;
			spherePos.x = sphere.x;
			spherePos.y = sphere.y;
			spherePos.z = sphere.z;
			float r = sphere.r;

			//範囲内との判定
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

			//角との判定
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

		//球と球との当たり判定
		static bool Collision(const CSphere& sphere1,const CSphere& sphere2)
		{
			return sphere1.CollisionSphere(sphere2);
		}

		static bool Collision(const CAABB& aabb1, const  CAABB& aabb2)
		{
			return aabb1.CollisionAABB(aabb2);
		}

		//敵と敵との当たり判定
		static void CollisionActorObject(CActorObject& obj1, CActorObject& obj2)
		{
			if (!obj1.IsShow() || !obj2.IsShow())
			{
				return;
			}
			//埋まり防止判定
			const Vector3& pos1 = obj1.GetPosition();
			const Vector3& pos2 = obj2.GetPosition();
			const CAABB& size1 = obj1.GetCollider();
			const CAABB& size2 = obj2.GetCollider();
			if (Collision(size1, size2))
			{

				//差分距離
				CVector3 sv = pos1 - pos2;

				Vector3 mv1 = pos1 - obj1.GetPrevPos();
				Vector3 mv2 = pos2 - obj2.GetPrevPos();
				Vector3 mv = mv1 - mv2;
				/*float ax = fabsf(mv1.x) + fabsf(mv2.x);
				float az = fabsf(mv1.z) + fabsf(mv2.z);
				float ml = ax > az ? ax : az;
				float dir = mv1.Dot(mv2);

				ax /= ml;
				az /= ml;
				*/
				//dir = mv1.x * mv2.x + mv1.y * mv2.y + mv1.z * mv2.z;

				float dir = sv.Dot(mv);
				if (dir > 0.0f)
				{
					float slx = copysignf((size1.Size.x + size2.Size.x) - (fabsf(sv.x)), sv.x);
					float slz = copysignf((size1.Size.z + size2.Size.z) - (fabsf(sv.z)), sv.z);
					obj1.SetPosition(pos1 + Vector3(slx * 0.5f, pos1.y, slz * 0.5f));
					obj2.SetPosition(pos2 - Vector3(slx * 0.5f, pos1.y, slz * 0.5f));
					//移動前の位置＋空いている分のベクトル
					/*float slx = copysignf((size1.Size.x + size2.Size.x) - (fabsf(sv.x) - 1), sv.x) * ax;
					float slz = copysignf((size1.Size.z + size2.Size.z) - (fabsf(sv.z) - 1), sv.z) * az;
					obj1.SetPosition(pos1 + Vector3(slx * 0.5f, pos1.y, slz * 0.5f));
					obj2.SetPosition(pos2 - Vector3(slx * 0.5f, pos1.y, slz * 0.5f));*/
				}
				else
				{
					
					obj1.SetPosition(Vector3(obj1.GetPrevPos().x, pos1.y, pos1.z + mv1.z));
					obj2.SetPosition(Vector3(obj2.GetPrevPos().x, pos2.y, pos2.z + mv2.z));
				}

				//お互いの間で空いているベクトルを計算
				//Vector3 
				
				

			}
		}

		/**
			 * @brief		当たり判定テンプレート関数
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




