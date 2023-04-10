#pragma once

#include "ResourceManager.h"
#include "Division.h"
#include "NormalMapParameter.h"

namespace ActionGame
{

	class CStageBase
	{
	protected:
		std::shared_ptr<CMeshContainer> stage_;
		MyClass::NormalMapParameterPtr shader_;
		DivisionArrayPtr divisionArray_;
		DivisionPtr currentDivision_;
		size_t phase_;
		bool isClear_;
	public:
		CStageBase();
		virtual ~CStageBase();
		virtual bool Load(const DivisionArrayPtr& divisionArray) = 0;
		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void RenderDebug() = 0;
		virtual void Release() = 0;
		virtual bool IsClear(const ClearTerm::ProviderPtr& provider) = 0;

		const ObjectPtr& GetObj(int divCount, int id)
		{
			assert(divisionArray_->at(divCount));
			return divisionArray_->at(divCount)->GetObj(id);
		}

		size_t GetEnemyCount() noexcept
		{
			size_t count = 0;
			for (auto& divition : *divisionArray_)
			{
				count += divition->GetEnemyCount();
			}
			return count;
		}

		size_t GetDivisionCount() const noexcept
		{
			return divisionArray_->size();
		}

		const DivisionPtr& GetDivision(size_t divCount)
		{
			assert(divisionArray_->at(divCount));
			return divisionArray_->at(divCount);
		}

		const DivisionPtr& GetCurrentDivision()
		{
			return currentDivision_;
		}

		void NextPhase();
	};

	using StagePtr = std::shared_ptr<CStageBase>;
}


