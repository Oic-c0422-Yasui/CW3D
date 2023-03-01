#include "StageManager.h"


using namespace ActionGame;

StageManager::StageManager()
{
}

StageManager::~StageManager()
{
}

bool ActionGame::StageManager::Load(const StagePtr& stage,const DivisionArrayPtr& divisions)
{
	stage_ = stage;
	if (!stage_->Load(divisions))
	{
		return false;
	}
	return true;
}

void ActionGame::StageManager::Initialize()
{
	stage_->Initialize();
}

void ActionGame::StageManager::Update()
{
	stage_->Update();
}

void ActionGame::StageManager::Render()
{
	stage_->Render();
}

void ActionGame::StageManager::RenderDebug()
{
	stage_->RenderDebug();
}

void ActionGame::StageManager::Release()
{
	stage_->Release();
}

bool ActionGame::StageManager::IsClear(const ClearTerm::ProviderPtr& provider)
{
	return stage_->IsClear(provider);
}