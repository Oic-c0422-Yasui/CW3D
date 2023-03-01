#include "StageBase.h"

using namespace ActionGame;

CStageBase::CStageBase()
	: phase_(0)
	, isClear_(false)
	, stage_(nullptr)
	, divisionArray_(nullptr)
	, currentDivision_(nullptr)
{
}

CStageBase::~CStageBase()
{
}

void ActionGame::CStageBase::Render()
{
	CMatrix44 matWorld;
	stage_->Render(matWorld);
}

void ActionGame::CStageBase::NextPhase()
{
	if (phase_ + 1 < GetDivisionCount())
	{
		phase_++;
		currentDivision_ = GetDivision(phase_);
	}
}


