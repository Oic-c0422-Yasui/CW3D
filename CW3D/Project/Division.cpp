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
}

void Sample::CDivision::Update()
{
	for (auto& clearTerm : m_Data.ClearTerms)
	{
		bool isClear = clearTerm->IsClear(m_ClearTermProvider);
		if (!isClear)
		{
			break;
		}
	}
	m_ClearFlg = true;
}

void Sample::CDivision::Release()
{
	m_Data.Enemys->clear();
	m_Data.Objects.clear();
	m_Data.ClearTerms.clear();
}
