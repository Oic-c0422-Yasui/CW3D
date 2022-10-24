#pragma once
#include "GameDefine.h"


namespace Sample
{

	class EnemyBuildParameter
	{
	private:
		std::string m_Type;
		Vector3 m_Pos;
	public:
		EnemyBuildParameter(const std::string& typeName,const Vector3& pos);
		~EnemyBuildParameter();

		const std::string& GetType()const noexcept
		{
			return m_Type;
		}

		const Vector3& GetPos() const noexcept
		{
			return m_Pos;
		}

	};

}


