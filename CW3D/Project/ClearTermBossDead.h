#pragma once
#include "IClearTerm.h"

namespace ClearTerm
{
	/*
	* @brief	クリア条件(ボスを倒す)
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