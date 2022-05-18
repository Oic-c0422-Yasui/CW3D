#pragma once

#include	"CollisionManager.h"
#include	"Player.h"
#include	"Enemy.h"

namespace Sample {

	template< >
	inline bool CollisionManager::Collision<CPlayer, CEnemy>(CPlayer& obj1, CEnemy& obj2) {
		//�G����\��

		//�G�̋�`�Ǝ����̋�`�Ń_���[�W
		CRectangle prec = obj1.GetRect();
		CRectangle erec = obj2.GetRect();
		if (prec.CollisionRect(erec))
		{
			obj1.Damage(5, 60, prec.Left < erec.Left);
			return true;
		}
		//�U�����̏ꍇ�̂ݍU���Ƃ̓����蔻������s
		if (!obj1.IsAttack())
		{
			return false;
		}
		//�G�̋�`�Ǝ����̍U����`�œG���_���[�W
		prec = obj1.GetAttackRect();
		if (prec.CollisionRect(erec))
		{
			obj2.Damage(5, obj1.IsReverse());
			return true;
		}
		return false;
	}

	template< >
	inline bool CollisionManager::Collision<CEnemy, CPlayer>(CEnemy& obj1, CPlayer& obj2) {
		return Collision(obj2, obj1);
	}
}