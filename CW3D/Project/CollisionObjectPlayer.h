#pragma once
#include "Collision.h"
#include "Player.h"
#include "Object.h"

namespace ActionGame
{
	/**
	 * @brief		敵と敵のあたり判定
	 */
	template < >
	inline void CCollision::CollisionObj<>(CPlayer& pl, CObject& obj) {
		//どちらかが非表示
		if (!pl.IsShow() || !obj.IsShow()) { return; }
		//埋まり防止判定
		CollisionObject(pl, obj);
	}
	template< >
	inline void CCollision::CollisionObj<>(CObject& obj, CPlayer& pl) {
		return CollisionObj(obj, pl);
	}

	/**
	 * @brief		敵とオブジェクトのあたり判定
	 */
	template < >
	inline void CCollision::CollisionObj<>(PlayerPtr& pl, ObjectPtr& obj) {
		CollisionObj(*pl, *obj);
	}

	/**
	 * @brief		敵とオブジェクトのあたり判定
	 */
	template < >
	inline void CCollision::CollisionObj<>(ObjectPtr& obj, PlayerPtr& pl) {
		CollisionObj(*pl, *obj);
	}
}

