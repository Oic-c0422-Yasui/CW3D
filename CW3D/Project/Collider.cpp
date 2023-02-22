#include "Collider.h"

MyUtil::CCollider2D::CCollider2D()
	: position_(0,0)
{
}

MyUtil::CCollider2D::CCollider2D(float x, float y)
	: position_(x,y)
{
}

MyUtil::CCollider2D::CCollider2D(Vector2 pos)
	:position_(pos)
{
}


MyUtil::CCollider3D::CCollider3D()
	:position_(0,0,0)
{
}

MyUtil::CCollider3D::CCollider3D(float x, float y, float z)
	:position_(x,y,z)
{
}

MyUtil::CCollider3D::CCollider3D(Vector3 pos)
	:position_(pos)
{
}
