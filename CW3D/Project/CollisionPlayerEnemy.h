#pragma once

#include	"Collision.h"
#include	"Player.h"
#include	"Enemy.h"

namespace ActionGame {

	template< >
	inline void CCollision::CollisionObj<>(CPlayer& obj1, Enemy& obj2) {
		//どちらかが非表示
		if (!obj1.IsShow() || !obj2.IsShow()) { return; }
		if (obj2.IsInvincible()) { return; }
		//埋まり防止判定
		CollisionActorObject(obj1, obj2);
	}

	template< >
	inline void CCollision::CollisionObj<>(Enemy& obj1, CPlayer& obj2) {
		return CollisionObj(obj1, obj2);
	}

	template< >
	inline void CCollision::CollisionObj<>(PlayerPtr& obj1, EnemyPtr& obj2) {
		return CollisionObj(*obj1, *obj2);
	}

	template< >
	inline void CCollision::CollisionObj<>(EnemyPtr& obj1, PlayerPtr& obj2) {
		return CollisionObj(*obj1, *obj2);
	}
}