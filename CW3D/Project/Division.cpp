#include "Division.h"

ActionGame::CDivision::CDivision(DIVISION_DATA data)
	: m_Data(data)
	, m_ClearFlg(false)
{
}

ActionGame::CDivision::~CDivision()
{
	Release();
}

void ActionGame::CDivision::Initialize()
{
	m_ClearFlg = false;
	for (auto& obj : m_Data.Objects)
	{
		obj->Initialize();
	}
}

void ActionGame::CDivision::Update()
{
	for (auto& obj : m_Data.Objects)
	{
		obj->Update();
	}

}

void ActionGame::CDivision::Release()
{
	m_Data.Objects.clear();
	m_Data.ClearTerms.clear();
	m_Data.EnemysParam.reset();
}

bool ActionGame::CDivision::IsClear(const ClearTermProviderPtr& provider)
{
	for (auto& clearTerm : m_Data.ClearTerms)
	{
		bool isClear = clearTerm->IsClear(provider);
		if (!isClear)
		{
			return false;
		}
	}
	return true;
}
