#include "ClearTermAllDeadAndEnduranceText.h"

Sample::ClearTermAllDeadAndEnduranceText::ClearTermAllDeadAndEnduranceText()
	: ClearTermText("")
	, allDead(std::make_shared<ClearTermEnemyAllDeadText>())
	, enduranceTime(std::make_shared<ClearTermEnduranceTimeText>())
{
}

void Sample::ClearTermAllDeadAndEnduranceText::Initialize()
{
}

void Sample::ClearTermAllDeadAndEnduranceText::Render()
{
	allDead->Render();
	enduranceTime->Render();
}
