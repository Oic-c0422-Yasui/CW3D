#include "Stage1.h"
#include "ResourceManager.h"

using namespace ActionGame;

ActionGame::CStage1::CStage1()
	:CStageBase()
{
}

bool ActionGame::CStage1::Load(const DivisionArrayPtr& divisionArray)
{
	 m_pStage = ResourcePtrManager<CMeshContainer>
							::GetInstance().GetResource("Stage", "StageMesh");

	 m_Divisions = divisionArray;
	 m_CurrentDivision = GetDivision(0);
	return true;
}

void ActionGame::CStage1::Initialize()
{

	m_ClearFlg = false;
	m_Phase = 0;
	for (auto& division : *m_Divisions)
	{
		division->Initialize();
	}

	m_CurrentDivision = GetDivision(m_Phase);
}

void ActionGame::CStage1::Update()
{
	if (m_ClearFlg)
	{
		return;
	}

	m_CurrentDivision->Update();
	

}

void ActionGame::CStage1::Render()
{
	CMatrix44 matWorld;
	m_pStage->Render(matWorld);
}

void ActionGame::CStage1::RenderDebug()
{
}

void ActionGame::CStage1::Release()
{
	m_pStage.reset();
	m_Divisions.reset();
	m_CurrentDivision.reset();
}

bool ActionGame::CStage1::IsClear(const ClearTermProviderPtr& provider)
{
	if (m_CurrentDivision->IsClear(provider))
	{
		m_CurrentDivision->ClearObject();
		//現在のフェーズが区画の数より大きいならクリア
		if (m_Phase + 1 >= m_Divisions->size())
		{
			return true;
		}
	}

	return false;
}
