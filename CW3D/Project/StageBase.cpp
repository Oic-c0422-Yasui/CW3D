#include "StageBase.h"

using namespace Sample;

CStageBase::CStageBase()
	: m_Phase(0)
	, m_pStage(nullptr)
	, m_Divisions(nullptr)
{
}

CStageBase::~CStageBase()
{
}

void Sample::CStageBase::Render()
{
}
