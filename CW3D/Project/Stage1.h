#pragma once
#include "StageBase.h"
#include "DivisionObject.h"


namespace Sample
{
    class CStage1 : public CStageBase
    {
	private:
	public:
		CStage1();
		bool Load(const DivisionArrayPtr& divisionArray) override;
		void Initialize() override;
		void Update() override;
		void Render() override;
		void RenderDebug() override;
		void Release() override;

    };
    using Stage1Ptr = std::shared_ptr<CStage1>;
}

