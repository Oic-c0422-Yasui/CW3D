#include "StageBase.h"

using namespace Sample;

CStageBase::CStageBase()
	: m_Phase(0)
	, m_ClearFlg(false)
	, m_pStage(nullptr)
	, m_Divisions(nullptr)
	, m_CurrentDivision(nullptr)
{
}

CStageBase::~CStageBase()
{
}

void Sample::CStageBase::Render()
{
	CMatrix44 matWorld;
	m_pStage->Render(matWorld);
}

void Sample::CStageBase::NextPhase()
{
	if (m_Phase + 1 < GetDivCount())
	{
		m_Phase++;
		m_CurrentDivision = GetDivision(m_Phase);
	}
}


