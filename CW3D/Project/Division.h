#pragma once
#include "GameDefine.h"

#include "Enemy.h"
#include "Object.h"
#include "IClearTerm.h"


namespace Sample
{
	class IClearTerm
	{
	public:
		virtual bool IsClear() = 0;
	};
	class ClearTermAllEnemyDead : public IClearTerm
	{
	protected:
		std::vector<EnemyPtr>* en;
	public:
		ClearTermAllEnemyDead(std::vector<EnemyPtr>* en)
			:en(en)
		{
		}
		bool IsClear() override
		{
			return true;
		}
	};
	class CDivision
	{
	public:
		struct DIVISION_DATA
		{
			std::vector<ClearTermPtr>	ClearTerms;
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


