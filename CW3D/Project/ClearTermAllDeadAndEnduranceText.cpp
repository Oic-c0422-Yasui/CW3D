#include "ClearTermAllDeadAndEnduranceText.h"

ClearTerm::CAllDeadAndEnduranceText::CAllDeadAndEnduranceText()
	: CClearTermText("")
	, allDead(std::make_shared<CEnemyAllDeadText>())
	, enduranceTime(std::make_shared<CEnduranceTimeText>())
{
}

void ClearTerm::CAllDeadAndEnduranceText::Initialize()
{
}

void ClearTerm::CAllDeadAndEnduranceText::Render()
{
	allDead->Render();
	enduranceTime->Render();
}
