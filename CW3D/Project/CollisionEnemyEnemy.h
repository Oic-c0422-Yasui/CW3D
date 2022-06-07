#pragma once
#include "Collision.h"
#include "Enemy.h"

namespace Sample
{
	/**
	 * @brief		�G�ƓG�̂����蔻��
	 */
	template < >
	inline void CCollision::CollisionObj<>(CEnemy& en1, CEnemy& en2) {
		//�ǂ��炩����\��
		if (!en1.IsShow() || !en2.IsShow()) { return; }
		//���܂�h�~����
		CollisionActorObject(en1, en2);
	}
}


