#include "ClearTermAllDeadAndEnduranceText.h"

ActionGame::ClearTermAllDeadAndEnduranceText::ClearTermAllDeadAndEnduranceText()
	: ClearTermText("")
	, allDead(std::make_shared<ClearTermEnemyAllDeadText>())
	, enduranceTime(std::make_shared<ClearTermEnduranceTimeText>())
{
}

void ActionGame::ClearTermAllDeadAndEnduranceText::Initialize()
{
}

void ActionGame::ClearTermAllDeadAndEnduranceText::Render()
{
	allDead->Render();
	enduranceTime->Render();
}
