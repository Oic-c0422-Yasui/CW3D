#pragma once
#include "GameDefine.h"


#include "EnemyBuildParameter.h"
#include "Object.h"
#include "IClearTerm.h"


namespace ActionGame
{
	class CDivision
	{
	public:
		struct DIVISION_DATA
		{
			ClearTermArray	ClearTerms;
			EnemyBuildParameterArrayPtr EnemysParam;
			int EnemyCount;
			std::vector<ObjectPtr> Objects;
			int ObjectCount;

			float width;
		};
	private:
		DIVISION_DATA m_Data;
		bool m_ClearFlg;
	public:
		CDivision(DIVISION_DATA data);
		~CDivision();


		void Initialize();
		void Update(const ClearTermProviderPtr& provider);
		void Release();

		const EnemyBuildParameterArrayPtr& GetEnemysParam()
		{
			return m_Data.EnemysParam;
		}

		const ObjectPtr& GetObj(size_t id)
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

		void Clear() noexcept
		{
			SetShowObjects(false);
		}

		void SetShowObjects(bool isShow) noexcept
		{
			for (auto& object : m_Data.Objects)
			{
				object->SetShow(isShow);
			}
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


