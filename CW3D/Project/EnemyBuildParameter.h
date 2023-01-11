#pragma once

#include "EnemyStatus.h"


namespace ActionGame
{
	
	struct EnemyParam
	{
	public:
		std::string m_Type;
		Vector3 m_Pos;
		bool m_IsBoss;

		EnemyParam(const std::string& type,const Vector3& pos,bool isBoss);
	};

	class EnemyBuildParameter
	{
	private:
		EnemyParam m_Param;
		EnemyStatusPtr m_Status;
	public:
		EnemyBuildParameter(const EnemyParam& param,const EnemyStatusPtr& status);
		~EnemyBuildParameter();

		const EnemyStatusPtr& GetStatus() const noexcept
		{
			return m_Status;
		}

		const EnemyParam& GetParam() const noexcept
		{
			return m_Param;
		}

	};
	using EnemyBuildParameterPtr = std::shared_ptr<EnemyBuildParameter>;
	using EnemyBuildParameterArray = std::vector<EnemyBuildParameterPtr>;
	using EnemyBuildParameterArrayPtr = std::shared_ptr<EnemyBuildParameterArray>;


}


