#pragma once
#include "StageBase.h"

namespace ActionGame
{
	class StageManager
	{
	private:
		StagePtr stage_;
	public:
		StageManager();
		~StageManager();
		bool Load(const StagePtr& stage, const DivisionArrayPtr& divisions);
		void Initialize();
		void Update();
		void Render();
		void RenderDebug();
		void Release();
		bool IsClear(const ClearTerm::ProviderPtr& provider);

		const ObjectPtr& GetObj(int divCount, int id)
		{
			return stage_->GetObj(divCount,id);
		}
		size_t GetDivitionObjCount(size_t divCount) const noexcept
		{
			return stage_->GetDivision(divCount)->GetObjCount();
		}

		size_t GetAllEnemyCount() const noexcept
		{
			return stage_->GetEnemyCount();
		}

		size_t GetDivisionEnemyCount(size_t divCount) const noexcept
		{
			return stage_->GetDivision(divCount)->GetEnemyCount();
		}

		size_t GetDivisionCount() const noexcept
		{
			return stage_->GetDivisionCount();
		}


		const DivisionPtr& GetDivision(size_t id)
		{
			return stage_->GetDivision(id);
		}

		const DivisionPtr& GetCurrentDivision()
		{
			return stage_->GetCurrentDivision();
		}

		void NextPhase()
		{
			stage_->NextPhase();
		}
	};
}


