#pragma once
#include "Collision.h"
#include "Player.h"
#include "Object.h"

namespace ActionGame
{
	/**
	 * @brief		�G�ƓG�̂����蔻��
	 */
	template < >
	inline void CCollision::CollisionObj<>(CPlayer& pl, CObject& obj) {
		//�ǂ��炩����\��
		if (!pl.IsShow() || !obj.IsShow()) { return; }
		//���܂�h�~����
		CollisionObject(pl, obj);
	}
	template< >
	inline void CCollision::CollisionObj<>(CObject& obj, CPlayer& pl) {
		return CollisionObj(obj, pl);
	}

	/**
	 * @brief		�G�ƃI�u�W�F�N�g�̂����蔻��
	 */
	template < >
	inline void CCollision::CollisionObj<>(PlayerPtr& pl, ObjectPtr& obj) {
		CollisionObj(*pl, *obj);
	}

	/**
	 * @brief		�G�ƃI�u�W�F�N�g�̂����蔻��
	 */
	template < >
	inline void CCollision::CollisionObj<>(ObjectPtr& obj, PlayerPtr& pl) {
		CollisionObj(*pl, *obj);
	}
}

