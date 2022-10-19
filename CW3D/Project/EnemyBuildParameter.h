#pragma once
#include "GameDefine.h"


namespace Sample
{

	class EnemyBuildParameter
	{
	private:
		int m_HP;
		float m_UltGauge;
		int m_Attack;
		std::string m_MeshName;
	public:
		EnemyBuildParameter(int hp,float ultGauge,int atk,std::string meshName);
		~EnemyBuildParameter();

		int GetHP() const noexcept
		{
			return m_HP;
		}

		float GetUltGauge()const noexcept
		{
			return m_UltGauge;
		}

		int GetAttack()const noexcept
		{
			return m_Attack;
		}

		const std::string& GetMeshName()const noexcept
		{
			return m_MeshName;
		}

	};

}


