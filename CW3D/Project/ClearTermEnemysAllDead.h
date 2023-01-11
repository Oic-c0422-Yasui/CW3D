#pragma once
#include "IClearTerm.h"

namespace ActionGame
{
	/*
	* @brief	�N���A����(�G�����ׂē|��)
	*/
	class ClearTermEnemysAllDead : public IClearTerm
	{
	private:

	public:
		ClearTermEnemysAllDead();
		bool IsClear(const ClearTermProviderPtr& provider) override;
		const std::string& GetType() const noexcept override { return "AllDead"; }
	};
}



