#pragma once
#include "IClearTerm.h"

namespace ClearTerm
{
	/*
	* @brief	�N���A����(�{�X��|��)
	*/
    class CBossDead :  public IClearTerm
    {
    private:

    public:
        CBossDead();
		bool IsClear(const ClearTerm::ProviderPtr& provider) override;
		const std::string& GetType() const noexcept override { return "BossDead"; }
    };

}