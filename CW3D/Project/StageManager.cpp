#include "StageManager.h"


using namespace ActionGame;

CStageManager::CStageManager()
{
}

CStageManager::~CStageManager()
{
}

bool ActionGame::CStageManager::Load(const StagePtr& stage,const DivisionArrayPtr& divisions)
{
	m_pStage = stage;
	if (!m_pStage->Load(divisions))
	{
		return false;
	}
	return true;
}

void ActionGame::CStageManager::Initialize()
{
	m_pStage->Initialize();
}

void ActionGame::CStageManager::Update(const ClearTermProviderPtr& provider)
{
	m_pStage->Update(provider);
}

void ActionGame::CStageManager::Render()
{
	m_pStage->Render();
}

void ActionGame::CStageManager::RenderDebug()
{
	m_pStage->RenderDebug();
}

void ActionGame::CStageManager::Release()
{
	m_pStage->Release();
}
