#pragma once
#include "GameDefine.h"
#include "ResourceManager.h"
#include "Division.h"

namespace Sample
{

	class CStageBase
	{
	protected:
		std::shared_ptr<CMeshContainer> m_pStage;
		DivisionArrayPtr m_Divisions;
		DivisionPtr m_CurrentDivision;
		int m_Phase;
	public:
		CStageBase();
		virtual ~CStageBase();
		virtual bool Load(const DivisionArrayPtr& divisionArray) = 0;
		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void RenderDebug() = 0;
		virtual void Release() = 0;

		const ObjectPtr& GetObj(int divCount, int id)
		{
			//int cnt = min(max(0, id), GetObjCount());
			return m_Divisions->at(divCount)->GetObj(id);
		}

		int GetEnemyCount() noexcept
		{
			int count = 0;
			for (auto& divition : *m_Divisions)
			{
				count += divition->GetEnemyCount();
			}
			return count;
		}

		/*const EnemyPtr& GetEnemy(int divCount,int id)
		{
			return m_Divisions->at(divCount)->GetEnemy(id);
		}*/

		int GetDivCount() const noexcept
		{
			return m_Divisions->size();
		}

		const DivisionPtr& GetDivision(int divCount)
		{
			return m_Divisions->at(divCount);
		}
	};

	using StagePtr = std::shared_ptr<CStageBase>;
}


