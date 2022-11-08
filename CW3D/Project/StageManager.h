#pragma once
#include "StageBase.h"

namespace Sample
{
	class CStageManager
	{
	private:
		StagePtr m_pStage;
	public:
		CStageManager();
		~CStageManager();
		bool Load(const StagePtr& stage);
		void Initialize();
		void Update(const ClearTermProviderPtr& provider);
		void Render();
		void RenderDebug();
		void Release();

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
	};
}


