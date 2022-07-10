#pragma once
#include "GameDefine.h"

#include "Enemy.h"
#include "Object.h"


namespace Sample
{
	class CDivision
	{
	public:
		struct DIVISION_DATA
		{
			std::vector<EnemyPtr>	Enemys;
			int EnemyCount;
			std::vector<ObjectPtr> Objects;
			int ObjectCount;
		};
	private:
		DIVISION_DATA m_Data;
	public:
		CDivision(DIVISION_DATA data) 
			: m_Data(data)
		{ 
		};
		~CDivision() {
			m_Data.Enemys.clear();
			m_Data.Objects.clear();
		};

		const ObjectPtr& GetObj(int id)
		{
			assert(m_Data.Objects[id]);
			return m_Data.Objects[id];
		}

		int GetObjCount() const noexcept
		{
			return m_Data.ObjectCount;
		}

		const EnemyPtr& GetEnemy(int id)
		{
			assert(m_Data.Enemys[id]);
			return m_Data.Enemys[id];
		}

		int GetEnemyCount() const noexcept
		{
			return m_Data.EnemyCount;
		}

	};

	using DivisionPtr = std::shared_ptr<CDivision>;
	using DivisionArray = std::vector<DivisionPtr>;
	using DivisionArrayPtr = std::shared_ptr<DivisionArray>;
}


