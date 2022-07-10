#pragma once
#include "Collision.h"
#include "Enemy.h"

namespace Sample
{
	/**
	 * @brief		敵と敵のあたり判定
	 */
	template < >
	inline void CCollision::CollisionObj<>(CEnemy& en1, CEnemy& en2) {
		//どちらかが非表示
		if (!en1.IsShow() || !en2.IsShow()) { return; }

		CVector3 sv = en1.GetPosition() - en2.GetPosition();

		//埋まり防止判定
		//CollisionActorObject(en1, en2);
	}

	/**
	 * @brief		敵と敵のあたり判定
	 */
	template < >
	inline void CCollision::CollisionObj<>(EnemyPtr& en1, EnemyPtr& en2) {
		CollisionObj(*en1, *en2);
	}
}


