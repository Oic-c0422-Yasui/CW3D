#include "Stage1.h"
#include "ResourceManager.h"

using namespace ActionGame;

ActionGame::CStage1::CStage1()
	:CStageBase()
{
}

bool ActionGame::CStage1::Load(const DivisionArrayPtr& divisionArray)
{
	 stage_ = ResourcePtrManager<CMeshContainer>
							::GetInstance().GetResource("Stage", "StageMesh");

	 divisionArray_ = divisionArray;
	 currentDivision_ = GetDivision(0);
	return true;
}

void ActionGame::CStage1::Initialize()
{

	isClear_ = false;
	phase_ = 0;
	for (auto& division : *divisionArray_)
	{
		division->Initialize();
	}

	currentDivision_ = GetDivision(phase_);
}

void ActionGame::CStage1::Update()
{
	if (isClear_)
	{
		return;
	}

	currentDivision_->Update();
	

}

void ActionGame::CStage1::Render()
{
	CMatrix44 matWorld;
	stage_->Render(matWorld);
}

void ActionGame::CStage1::RenderDebug()
{
}

void ActionGame::CStage1::Release()
{
	stage_.reset();
	divisionArray_.reset();
	currentDivision_.reset();
}

bool ActionGame::CStage1::IsClear(const ClearTerm::ProviderPtr& provider)
{
	if (currentDivision_->IsClear(provider))
	{
		currentDivision_->ClearObject();
		//現在のフェーズが区画の数より大きいならクリア
		if (phase_ + 1 >= divisionArray_->size())
		{
			return true;
		}
	}

	return false;
}
