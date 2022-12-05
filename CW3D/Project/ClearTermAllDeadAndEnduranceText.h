#pragma once
#include "ClearTermText.h"
#include "ClearTermEnduranceTimeText.h"
#include "ClearTermEnemyAllDeadText.h"

namespace ActionGame
{

    class ClearTermAllDeadAndEnduranceText : public ClearTermText
    {
    private:
        ClearTermEnemyAllDeadTextPtr allDead;
        ClearTermEnduranceTimeTextPtr enduranceTime;
    public:
        ClearTermAllDeadAndEnduranceText();

        void Initialize() override;
        void Render() override;

        float GetRenderHeight() {}

        const ClearTermEnemyAllDeadTextPtr& GetAllDeadTerm() const noexcept { return allDead; }
    };

    using ClearTermAllDeadAndEnduranceTextPtr = std::shared_ptr<ClearTermAllDeadAndEnduranceText>;
}


