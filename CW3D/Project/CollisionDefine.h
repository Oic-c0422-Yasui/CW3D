#pragma once

//当たり判定のタイプ
enum tag_COLLISIONTYPE
{
	COLLISION_SPHERE,	//球体
	COLLISION_AABB,		//箱
	COLLISION_OBB,		//回転を考慮した箱
};