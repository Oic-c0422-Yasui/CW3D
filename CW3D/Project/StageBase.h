#pragma once
#include "GameDefine.h"
#include "ResourceManager.h"
#include "Division.h"

namespace ActionGame
{

	class CStageBase
	{
	protected:
		std::shared_ptr<CMeshContainer> m_pStage;
		DivisionArrayPtr m_Divisions;
		DivisionPtr m_CurrentDivision;
		int m_Phase;
		bool m_ClearFlg;
	public:
		CStageBase();
		virtual ~CStageBase();
		virtual bool Load(const DivisionArrayPtr& divisionArray) = 0;
		virtual void Initialize() = 0;
		virtual void Update(const ClearTermProviderPtr& provider) = 0;
		virtual void Render() = 0;
		virtual void RenderDebug() = 0;
		virtual void Release() = 0;

		const ObjectPtr& GetObj(int divCount, int id)
		{
			assert(m_Divisions->at(divCount));
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

		int GetDivCount() const noexcept
		{
			return m_Divisions->size();
		}

		const DivisionPtr& GetDivision(size_t divCount)
		{
			assert(m_Divisions->at(divCount));
			return m_Divisions->at(divCount);
		}

		const DivisionPtr& GetCurrentDivision()
		{
			return m_CurrentDivision;
		}

		bool IsClear() const noexcept
		{
			return m_ClearFlg;
		}

		void NextPhase();
	};

	using StagePtr = std::shared_ptr<CStageBase>;
}


