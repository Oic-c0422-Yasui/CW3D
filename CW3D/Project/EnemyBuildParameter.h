#pragma once

#include "EnemyStatus.h"


namespace ActionGame
{
	
	struct EnemyParam
	{
	public:
		std::string type_;
		Vector3 position_;
		bool isBoss_;

		EnemyParam(const std::string& type,const Vector3& pos,bool isBoss);
	};

	class EnemyBuildParameter
	{
	private:
		EnemyParam param_;
		EnemyStatusPtr status_;
	public:
		EnemyBuildParameter(const EnemyParam& param,const EnemyStatusPtr& status);
		~EnemyBuildParameter();

		const EnemyStatusPtr& GetStatus() const noexcept
		{
			return status_;
		}

		const EnemyParam& GetParam() const noexcept
		{
			return param_;
		}

	};
	using EnemyBuildParameterPtr = std::shared_ptr<EnemyBuildParameter>;
	using EnemyBuildParameterArray = std::vector<EnemyBuildParameterPtr>;
	using EnemyBuildParameterArrayPtr = std::shared_ptr<EnemyBuildParameterArray>;


}


