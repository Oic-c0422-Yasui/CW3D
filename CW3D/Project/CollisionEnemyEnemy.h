#pragma once
#include "Collision.h"
#include "Enemy.h"

namespace Sample
{
	/**
	 * @brief		“G‚Æ“G‚Ì‚ ‚½‚è”»’è
	 */
	template < >
	inline void CCollision::CollisionObj<>(CEnemy& en1, CEnemy& en2) {
		//‚Ç‚¿‚ç‚©‚ª”ñ•\Ž¦
		if (!en1.IsShow() || !en2.IsShow()) { return; }

		CVector3 sv = en1.GetPosition() - en2.GetPosition();

		//–„‚Ü‚è–hŽ~”»’è
		//CollisionActorObject(en1, en2);
	}

	/**
	 * @brief		“G‚Æ“G‚Ì‚ ‚½‚è”»’è
	 */
	template < >
	inline void CCollision::CollisionObj<>(EnemyPtr& en1, EnemyPtr& en2) {
		CollisionObj(*en1, *en2);
	}
}


