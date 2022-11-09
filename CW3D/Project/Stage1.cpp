#include "Stage1.h"
#include "ResourceManager.h"

using namespace Sample;

Sample::CStage1::CStage1()
	:CStageBase()
{
}

bool Sample::CStage1::Load(const DivisionArrayPtr& divisionArray)
{
	 m_pStage = ResourcePtrManager<CMeshContainer>
							::GetInstance().GetResource("Stage", "StageMesh");

	 m_Divisions = divisionArray;
	 m_CurrentDivision = GetDivision(0);
	return true;
}

void Sample::CStage1::Initialize()
{

	m_ClearFlg = false;
	m_Phase = 0;
	for (auto& division : *m_Divisions)
	{
		division->Initialize();
	}

	m_CurrentDivision = GetDivision(m_Phase);
}

void Sample::CStage1::Update(const ClearTermProviderPtr& provider)
{
	if (m_ClearFlg)
	{
		return;
	}

	m_CurrentDivision->Update(provider);
	
	if (m_CurrentDivision->IsClear())
	{
		m_CurrentDivision->Clear();
		if (m_Phase + 1 >= m_Divisions->size())
		{
			m_ClearFlg = true;
		}
	}

}

void Sample::CStage1::Render()
{
	CMatrix44 matWorld;
	m_pStage->Render(matWorld);
}

void Sample::CStage1::RenderDebug()
{
}

void Sample::CStage1::Release()
{
	m_pStage.reset();
	m_Divisions.reset();
	m_CurrentDivision.reset();
}
