#pragma once

//当たり判定のタイプ
enum COLLISION_TYPE
{
	SPHERE,	//球体
	AABB,		//箱
	OBB,		//回転を考慮した箱
};