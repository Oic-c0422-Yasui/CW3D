#pragma once
#include "GameDefine.h"
#include "EnemyStatus.h"

namespace Sample
{
	
	class EnemyParam
	{
	public:
		std::string m_Type;
		Vector3 m_Pos;

		EnemyParam(const std::string& type,const Vector3& pos);
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


