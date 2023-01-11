#pragma once
#include "IClearTerm.h"

namespace ActionGame
{
	/*
	* @brief	ƒNƒŠƒAğŒ(“G‚ğ‚·‚×‚Ä“|‚·)
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



