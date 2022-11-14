#include "Division.h"

Sample::CDivision::CDivision(DIVISION_DATA data)
	: m_Data(data)
	, m_ClearFlg(false)
{
}

Sample::CDivision::~CDivision()
{
	Release();
}

void Sample::CDivision::Initialize()
{
	m_ClearFlg = false;
	for (auto& obj : m_Data.Objects)
	{
		obj->Initialize();
	}
}

void Sample::CDivision::Update(const ClearTermProviderPtr& provider)
{
	for (auto& obj : m_Data.Objects)
	{
		obj->Update();
	}

	for (auto& clearTerm : m_Data.ClearTerms)
	{
		bool isClear = clearTerm->IsClear(provider);
		if (!isClear)
		{
			return;
		}
	}
	m_ClearFlg = true;
}

void Sample::CDivision::Release()
{
	m_Data.Objects.clear();
	m_Data.ClearTerms.clear();
}
