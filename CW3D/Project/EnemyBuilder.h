#pragma once
#include "Enemy.h"
#include "IInput.h"

namespace Sample
{
	class CEnemyBuilder {
	public:
		EnemyPtr Create(Vector3 pos) {
			EnemyPtr enemy = std::make_shared<CEnemy>();
			enemy->Load();
			enemy->Initialize(pos);
			return enemy;
		}
	};
}

