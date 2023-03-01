#include "Division.h"

ActionGame::CDivision::CDivision(DIVISION_DATA data)
	: data_(data)
	, isClear_(false)
{
}

ActionGame::CDivision::~CDivision()
{
	Release();
}

void ActionGame::CDivision::Initialize()
{
	isClear_ = false;
	for (auto& obj : data_.Objects)
	{
		obj->Initialize();
	}
}

void ActionGame::CDivision::Update()
{
	for (auto& obj : data_.Objects)
	{
		obj->Update();
	}

}

void ActionGame::CDivision::Release()
{
	data_.Objects.clear();
	data_.ClearTerms.clear();
	data_.EnemysParam.reset();
}

bool ActionGame::CDivision::IsClear(const ClearTerm::ProviderPtr& provider)
{
	for (auto& clearTerm : data_.ClearTerms)
	{
		bool isClear = clearTerm->IsClear(provider);
		if (!isClear)
		{
			return false;
		}
	}
	return true;
}
