#pragma once
#include "ColliderBase.h"
#include "Common.h"

namespace MyUtil
{
	/*
	* @brief	2D用コライダークラス
	*/
	class CCollider2D : public CColliderBase
	{
	protected:
		Vector2		position_;
	public:
		CCollider2D();
		CCollider2D(float x, float y);
		CCollider2D(Vector2 pos);
		~CCollider2D() override = default;
		virtual bool IsCollision(const CColliderBase& collider) override = 0;
		virtual bool IsCollision(const ColliderPtr& collider) override = 0;
	};

	/*
	* @brief	3D用コライダークラス
	*/
	class CCollider3D : public CColliderBase
	{
	protected:
		Vector3		position_;
	public:
		CCollider3D();
		CCollider3D(float x, float y,float z);
		CCollider3D(Vector3 pos);
		~CCollider3D() override = default;
		virtual bool IsCollision(const CColliderBase& collider) override = 0;
		virtual bool IsCollision(const ColliderPtr& collider) override = 0;
	};
}


