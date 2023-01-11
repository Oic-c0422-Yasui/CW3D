#pragma once
#include "IClearTerm.h"

namespace ActionGame
{
	/*
	* @brief	クリア条件(ボスを倒す)
	*/
    class ClearTermBossDead :  public IClearTerm
    {
    private:

    public:
        ClearTermBossDead();
		bool IsClear(const ClearTermProviderPtr& provider) override;
		const std::string& GetType() const noexcept override { return "BossDead"; }
    };

}