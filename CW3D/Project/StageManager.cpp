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
	m_pStage = stage;
	if (!m_pStage->Load(divisions))
	{
		return false;
	}
	return true;
}

void ActionGame::StageManager::Initialize()
{
	m_pStage->Initialize();
}

void ActionGame::StageManager::Update()
{
	m_pStage->Update();
}

void ActionGame::StageManager::Render()
{
	m_pStage->Render();
}

void ActionGame::StageManager::RenderDebug()
{
	m_pStage->RenderDebug();
}

void ActionGame::StageManager::Release()
{
	m_pStage->Release();
}

bool ActionGame::StageManager::IsClear(const ClearTermProviderPtr& provider)
{
	return m_pStage->IsClear(provider);
}