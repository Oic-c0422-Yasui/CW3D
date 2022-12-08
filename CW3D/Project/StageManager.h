#pragma once
#include "StageBase.h"

namespace ActionGame
{
	class CStageManager
	{
	private:
		StagePtr m_pStage;
	public:
		CStageManager();
		~CStageManager();
		bool Load(const StagePtr& stage, const DivisionArrayPtr& divisions);
		void Initialize();
		void Update();
		void Render();
		void RenderDebug();
		void Release();
		bool IsClear(const ClearTermProviderPtr& provider);

		const ObjectPtr& GetObj(int divCount, int id)
		{
			return m_pStage->GetObj(divCount,id);
		}
		int GetDivObjCount(int divCount) const noexcept
		{
			return m_pStage->GetDivision(divCount)->GetObjCount();
		}

		int GetAllEnemyCount() const noexcept
		{
			return m_pStage->GetEnemyCount();
		}

		int GetDivEnemyCount(int divCount) const noexcept
		{
			return m_pStage->GetDivision(divCount)->GetEnemyCount();
		}

		int GetDivCount() const noexcept
		{
			return m_pStage->GetDivCount();
		}


		const DivisionPtr& GetDivision(size_t id)
		{
			return m_pStage->GetDivision(id);
		}

		const DivisionPtr& GetCurrentDivision()
		{
			return m_pStage->GetCurrentDivision();
		}

		void NextPhase()
		{
			m_pStage->NextPhase();
		}
	};
}


