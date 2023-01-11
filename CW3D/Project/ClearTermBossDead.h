#pragma once
#include "IClearTerm.h"

namespace ActionGame
{
	/*
	* @brief	�N���A����(�{�X��|��)
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