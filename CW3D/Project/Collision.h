#pragma once
#include "Common.h"
#include "Enemy.h"

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


		//球と立方体との当たり判定
		static bool Collition(const CSphere& sphere, const CAABB& aabb)
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
		static bool Collition(CSphere sphere1, CSphere sphere2)
		{
			return sphere1.CollisionSphere(sphere2);
		}

		//敵と敵との当たり判定
		static void CollisionEnemyEnemy(CEnemy*& enemy1, CEnemy*& enemy2)
		{
			if (!enemy1->IsShow() || !enemy2->IsShow())
			{
				return;
			}
			//埋まり防止判定
			const Vector3& pos1 = enemy1->GetPosition();
			const Vector3& pos2 = enemy2->GetPosition();
			const CSphere& sphere1 = enemy1->GetCollider();
			const CSphere& sphere2 = enemy2->GetCollider();
			if (Collition(sphere1, sphere2))
			{

				//差分距離
				Vector3 sv = pos1 - pos2;
				//お互いの移動ベクトル
				float ax = fabsf(pos1.x) + fabsf(pos2.x);
				float az = fabsf(pos1.z) + fabsf(pos2.z);
				float ml = ax > az ? ax : az;
				//移動していないのに接触？
				if (ml <= 0)
				{
					//その場合埋まりの割合で押し出し
					ax = fabsf(sv.x) / (sphere1.r + sphere2.r);
					az = fabsf(sv.z) / (sphere1.r + sphere2.r);
					ml = ax > az ? ax : az;
				}
				ax /= ml;
				az /= ml;
				//埋まり防止をおこなう
				float slx = copysignf((sphere1.r + sphere1.r) - (fabsf(sv.x) - 1), sv.x) * ax;
				float slz = copysignf((sphere1.r + sphere1.r) - (fabsf(sv.z) - 1), sv.z) * az;
				enemy1->SetPosition(pos1 + Vector3(slx * 0.5f, 0.0f, slz * 0.5f));
				enemy2->SetPosition(pos2 - Vector3(slx * 0.5f, 0.0f, slz * 0.5f));

			}
		}

	};
}



