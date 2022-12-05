#pragma once
#include "IClearTerm.h"
#include "Enemy.h"

namespace ActionGame
{
	/*
	* @brief	�N���A����(�G�����ׂē|��)
	*/
	class ClearTermEnemysAllDead : public IClearTerm
	{
	private:
		EnemyArrayPtr m_Enemys;
	public:
		ClearTermEnemysAllDead();
		bool IsClear(const ClearTermProviderPtr& provider) override;
		const std::string& GetType() override { return "AllDead"; }
	};
}



