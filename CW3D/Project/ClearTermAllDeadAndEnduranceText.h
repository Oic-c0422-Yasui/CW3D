#pragma once
#include "ClearTermText.h"
#include "ClearTermEnduranceTimeText.h"
#include "ClearTermEnemyAllDeadText.h"

namespace ClearTerm
{

    class CAllDeadAndEnduranceText : public CClearTermText
    {
    private:
        EnemyAllDeadTextPtr allDead;
        EnduranceTimeTextPtr enduranceTime;
    public:
        CAllDeadAndEnduranceText();

        void Initialize() override;
        void Render() override;

        float GetRenderHeight() {}

        const EnemyAllDeadTextPtr& GetAllDeadTerm() const noexcept { return allDead; }
    };

    using AllDeadAndEnduranceTextPtr = std::shared_ptr<CAllDeadAndEnduranceText>;
}


