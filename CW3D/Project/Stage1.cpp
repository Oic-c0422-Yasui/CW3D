#include "Stage1.h"

using namespace Sample;

Sample::CStage1::CStage1()
	:CStageBase()
{
}

bool Sample::CStage1::Load()
{
	m_pStage = std::make_shared<CMeshContainer>();
	if (!m_pStage->Load("Stage/stage.mom"))
	{
		return false;
	}
	m_Divisions = JsonDivisionCreator::Create("Text/Division.json");


	return true;
}

void Sample::CStage1::Initialize()
{

	for (auto& obj : *m_Divisions)
	{
		for (int i = 0; i < obj->GetObjCount(); i++)
		{
			obj->GetObj(i)->Initialize();
		}
	}
	m_Phase = 0;
	for (int i = 1; i < GetDivCount(); i++)
	{
		for (int j = 0; j < m_Divisions->at(i)->GetEnemyCount(); j++)
		{
			auto& enemy = m_Divisions->at(i)->GetEnemy(j);
			enemy->SetShow(false);
		}
	}
}

void Sample::CStage1::Update()
{
	for (auto& obj : *m_Divisions)
	{
		for (int i = 0; i < obj->GetObjCount(); i++)
		{
			obj->GetObj(i)->Update();
		}
	}

	int cnt = 0;
	auto currentDiv = m_Divisions->at(m_Phase);
	for (int i = 0; i < currentDiv->GetEnemyCount(); i++)
	{
		if (!currentDiv->GetEnemy(i)->IsShow())
		{
			cnt++;
		}
	}
	if (cnt >= currentDiv->GetEnemyCount() && m_Phase < GetDivCount() - 1)
	{
		for (int i = 0; i < currentDiv->GetObjCount(); i++)
		{
			currentDiv->GetObj(i)->SetShow(false);
		}
		m_Phase++;
		auto nextDiv = m_Divisions->at(m_Phase);
		for (int i = 0; i < nextDiv->GetEnemyCount(); i++)
		{
			nextDiv->GetEnemy(i)->SetShow(true);
		}
	}

}

void Sample::CStage1::Render()
{
	CMatrix44 matWorld;
	m_pStage->Render(matWorld);

	for (auto& obj : *m_Divisions)
	{
		for (int i = 0; i < obj->GetObjCount(); i++)
		{
			obj->GetObj(i)->Render();
		}
	}
}

void Sample::CStage1::RenderDebug()
{
}

void Sample::CStage1::Release()
{
	m_pStage.reset();
	m_Divisions.reset();
}