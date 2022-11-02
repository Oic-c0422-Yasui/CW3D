#pragma once
#include "GameDefine.h"


#include "EnemyBuildParameter.h"
#include "Object.h"
#include "IClearTerm.h"


namespace Sample
{
	class CDivision
	{
	public:
		struct DIVISION_DATA
		{
			ClearTermArray	ClearTerms;
			std::vector<EnemyBuildParameter> EnemysParam;
			EnemyArrayPtr	Enemys;
			int EnemyCount;
			std::vector<ObjectPtr> Objects;
			int ObjectCount;
		};
	private:
		DIVISION_DATA m_Data;
		bool m_ClearFlg;
		ClearTermProviderPtr m_ClearTermProvider;
	public:
		CDivision(DIVISION_DATA data);
		~CDivision();


		void Initialize();
		void Update();
		void Release();

		const std::vector<EnemyBuildParameter>& GetEnemysParam()
		{
			return m_Data.EnemysParam;
		}

		const ObjectPtr& GetObj(int id)
		{
			assert(m_Data.Objects[id]);
			return m_Data.Objects[id];
		}

		int GetObjCount() const noexcept
		{
			return m_Data.ObjectCount;
		}

		int GetEnemyCount() const noexcept
		{
			return m_Data.EnemyCount;
		}


		bool IsClear() const noexcept
		{
			return m_ClearFlg;
		}
	};

	using DivisionPtr = std::shared_ptr<CDivision>;
	using DivisionArray = std::vector<DivisionPtr>;
	using DivisionArrayPtr = std::shared_ptr<DivisionArray>;
}


