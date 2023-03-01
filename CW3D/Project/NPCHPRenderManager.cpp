#include "NPCHPRenderManager.h"

ActionGame::CNPCHPRenderManager::CNPCHPRenderManager()
{
}

ActionGame::CNPCHPRenderManager::~CNPCHPRenderManager()
{
}

bool ActionGame::CNPCHPRenderManager::Load()
{
	for (auto normal : normalHPRender_)
	{
		if (!normal->Load())
		{
			return false;
		}
		
	}
	for (auto boss : bossHPRender_)
	{
		if (!boss->Load())
		{
			return false;
		}
	}
	return true;
}

void ActionGame::CNPCHPRenderManager::Initialize()
{
	for (auto normal : normalHPRender_)
	{
		normal->Initialize();
	}
	for (auto boss : bossHPRender_)
	{
		boss->Initialize();
	}

}

void ActionGame::CNPCHPRenderManager::Render()
{
	//“GHPƒo[‚Ì•`‰æ“ü‚ê‘Ö‚¦
	Sort();

	for (auto normal : normalHPRender_)
	{
		normal->Render();
	}
	
}

void ActionGame::CNPCHPRenderManager::Render2D()
{
	for (auto boss : bossHPRender_)
	{
		boss->Render();
	}
}

void ActionGame::CNPCHPRenderManager::Release()
{
	for (auto normal : normalHPRender_)
	{
		normal->Release();
	}
	for (auto boss : bossHPRender_)
	{
		boss->Release();
	}
	normalHPRender_.clear();
	bossHPRender_.clear();
}

void ActionGame::CNPCHPRenderManager::Reset()
{
	normalHPRender_.clear();
	bossHPRender_.clear();
}

void ActionGame::CNPCHPRenderManager::Sort()
{
	//HPƒo[‚Ì•`‰æ“ü‚ê‘Ö‚¦
	std::sort(normalHPRender_.begin(), normalHPRender_.end(),
		[](ActionGame::NormalEnemyHPRenderPtr& obj1, ActionGame::NormalEnemyHPRenderPtr& obj2)
		{
			return obj1->GetViewPosition().z > obj2->GetViewPosition().z;
		});
}

void ActionGame::CNPCHPRenderManager::Add(const NormalEnemyHPRenderPtr& render)
{
	normalHPRender_.push_back(render);
}

void ActionGame::CNPCHPRenderManager::Add(const BossHPRenderPtr& render)
{
	bossHPRender_.push_back(render);
}
