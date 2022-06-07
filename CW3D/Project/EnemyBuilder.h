#pragma once
#include "Enemy.h"
#include "IInput.h"

class CEnemyBuilder {
public:
	Sample::EnemyPtr Create(Vector3 pos) {
		Sample::EnemyPtr enemy = std::make_shared<Sample::CEnemy>();
		enemy->Load();
		enemy->Initialize(pos);
		return enemy;
	}
};