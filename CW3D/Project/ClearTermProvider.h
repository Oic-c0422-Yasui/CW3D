#pragma once
#include "GameDefine.h"
#include "Enemy.h"

namespace Sample
{
	class ClearTermProvider
	{
	private:
		float m_ClearTime;
		std::vector<EnemyPtr> m_pEnemys;
	public:
		//TODO:ƒ{ƒX‚ð’Ç‰Á‚·‚é
		ClearTermProvider(std::vector<EnemyPtr> enemys, float time):
			m_ClearTime(time),
			m_pEnemys(enemys)
		{
			
		}
	};
}