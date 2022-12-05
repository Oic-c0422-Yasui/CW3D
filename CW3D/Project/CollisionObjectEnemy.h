#pragma once
#include "Collision.h"
#include "Enemy.h"
#include "Object.h"

namespace ActionGame
{
	/**
	 * @brief		敵と敵のあたり判定
	 */
	template < >
	inline void CCollision::CollisionObj<>(CEnemy& ene, CObject& obj) {
		//どちらかが非表示
		if (!ene.IsShow() || !obj.IsShow()) { return; }
		//埋まり防止判定
		CollisionObject(ene, obj);
	}
	template< >
	inline void CCollision::CollisionObj<>(CObject& obj, CEnemy& ene) {
		return CollisionObj(obj, ene);
	}

	/**
	 * @brief		敵とオブジェクトのあたり判定
	 */
	template < >
	inline void CCollision::CollisionObj<>(EnemyPtr& ene, ObjectPtr& obj) {
		CollisionObj(*ene, *obj);
	}

	/**
	 * @brief		敵とオブジェクトのあたり判定
	 */
	template < >
	inline void CCollision::CollisionObj<>(ObjectPtr& obj, EnemyPtr& ene) {
		CollisionObj(*ene, *obj);
	}
}


