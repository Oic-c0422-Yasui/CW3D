#include "StageManager.h"


using namespace Sample;

CStageManager::CStageManager()
{
}

CStageManager::~CStageManager()
{
}

bool Sample::CStageManager::Load(const StagePtr& stage)
{
	m_pStage = stage;
	if (!m_pStage->Load())
	{
		return false;
	}
	return true;
}

void Sample::CStageManager::Initialize()
{
	m_pStage->Initialize();
}

void Sample::CStageManager::Update(const ClearTermProviderPtr& provider)
{
	m_pStage->Update(provider);
}

void Sample::CStageManager::Render()
{
	m_pStage->Render();
}

void Sample::CStageManager::RenderDebug()
{
	m_pStage->RenderDebug();
}

void Sample::CStageManager::Release()
{
	m_pStage->Release();
}
