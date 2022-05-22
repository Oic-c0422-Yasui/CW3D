#pragma once

#include	"CollisionManager.h"
#include	"Player.h"
#include	"Enemy.h"

namespace Sample {

	template< >
	inline bool CollisionManager::Collision<CPlayer, CEnemy>(CPlayer& obj1, CEnemy& obj2) {

		
	}

	template< >
	inline bool CollisionManager::Collision<CEnemy, CPlayer>(CEnemy& obj1, CPlayer& obj2) {
		return Collision(obj2, obj1);
	}
}