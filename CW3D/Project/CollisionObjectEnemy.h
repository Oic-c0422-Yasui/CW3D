#pragma once
#include "Collision.h"
#include "Enemy.h"
#include "Object.h"

namespace ActionGame
{
	/**
	 * @brief		�G�ƓG�̂����蔻��
	 */
	template < >
	inline void CCollision::CollisionObj<>(CEnemy& ene, CObject& obj) {
		//�ǂ��炩����\��
		if (!ene.IsShow() || !obj.IsShow()) { return; }
		//���܂�h�~����
		CollisionObject(ene, obj);
	}
	template< >
	inline void CCollision::CollisionObj<>(CObject& obj, CEnemy& ene) {
		return CollisionObj(obj, ene);
	}

	/**
	 * @brief		�G�ƃI�u�W�F�N�g�̂����蔻��
	 */
	template < >
	inline void CCollision::CollisionObj<>(EnemyPtr& ene, ObjectPtr& obj) {
		CollisionObj(*ene, *obj);
	}

	/**
	 * @brief		�G�ƃI�u�W�F�N�g�̂����蔻��
	 */
	template < >
	inline void CCollision::CollisionObj<>(ObjectPtr& obj, EnemyPtr& ene) {
		CollisionObj(*ene, *obj);
	}
}


