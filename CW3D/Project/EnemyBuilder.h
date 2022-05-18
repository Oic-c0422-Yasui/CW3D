#pragma once
#include "Enemy.h"
#include "IInput.h"

class CEnemyBuilder {
public:
	CEnemy* Create(Vector3 pos) {
		CEnemy* enemy = new CEnemy();
		enemy->Load();
		enemy->Initialize(pos);
		return enemy;
	}
};