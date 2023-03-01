#pragma once
#include "IClearTerm.h"

namespace ClearTerm
{
	/*
	* @brief	�N���A����(�G�����ׂē|��)
	*/
	class CEnemysAllDead : public IClearTerm
	{
	public:
		CEnemysAllDead();
		bool IsClear(const ProviderPtr& provider) override;
		const std::string& GetType() const noexcept override { return "AllDead"; }
	};
}



