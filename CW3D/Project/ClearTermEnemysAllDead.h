#pragma once
#include "IClearTerm.h"

namespace ClearTerm
{
	/*
	* @brief	ƒNƒŠƒAğŒ(“G‚ğ‚·‚×‚Ä“|‚·)
	*/
	class CEnemysAllDead : public IClearTerm
	{
	public:
		CEnemysAllDead();
		bool IsClear(const ProviderPtr& provider) override;
		const std::string& GetType() const noexcept override { return "AllDead"; }
	};
}



