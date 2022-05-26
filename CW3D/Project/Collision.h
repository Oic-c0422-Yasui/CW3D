#pragma once
#include "Common.h"

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

	

	static bool Collition(const CSphere& sphere, const CAABB& aabb)
	{

		Vector3 boxMin = aabb.Position - aabb.Size;
		Vector3 boxMax = aabb.Position + aabb.Size;
		Vector3 spherePos;
		spherePos.x = sphere.x;
		spherePos.y = sphere.y;
		spherePos.z = sphere.z;
		float r = sphere.r;

		//”ÍˆÍ“à‚Æ‚Ì”»’è
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

		//Šp‚Æ‚Ì”»’è
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

	static bool Collition(CSphere sphere1, CSphere sphere2)
	{
		return sphere1.CollisionSphere(sphere2);
	}



};

