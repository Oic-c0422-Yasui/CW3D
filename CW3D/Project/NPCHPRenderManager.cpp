#include "NPCHPRenderManager.h"

ActionGame::NPCHPRenderManager::NPCHPRenderManager()
{
}

ActionGame::NPCHPRenderManager::~NPCHPRenderManager()
{
}

bool ActionGame::NPCHPRenderManager::Load()
{
	for (auto normal : m_NormalHPRender)
	{
		if (!normal->Load())
		{
			return false;
		}
		
	}
	for (auto boss : m_BossHPRender)
	{
		if (!boss->Load())
		{
			return false;
		}
	}
	return true;
}

void ActionGame::NPCHPRenderManager::Initialize()
{
	for (auto normal : m_NormalHPRender)
	{
		normal->Initialize();
	}
	for (auto boss : m_BossHPRender)
	{
		boss->Initialize();
	}

}

void ActionGame::NPCHPRenderManager::Render()
{
	//“GHPƒo[‚Ì•`‰æ“ü‚ê‘Ö‚¦
	Sort();

	for (auto normal : m_NormalHPRender)
	{
		normal->Render();
	}
	
}

void ActionGame::NPCHPRenderManager::Render2D()
{
	for (auto boss : m_BossHPRender)
	{
		boss->Render();
	}
}

void ActionGame::NPCHPRenderManager::Release()
{
	for (auto normal : m_NormalHPRender)
	{
		normal->Release();
	}
	for (auto boss : m_BossHPRender)
	{
		boss->Release();
	}
	m_NormalHPRender.clear();
	m_BossHPRender.clear();
}

void ActionGame::NPCHPRenderManager::Reset()
{
	m_NormalHPRender.clear();
	m_BossHPRender.clear();
}

void ActionGame::NPCHPRenderManager::Sort()
{
	//“GHPƒo[‚Ì•`‰æ“ü‚ê‘Ö‚¦
	std::sort(m_NormalHPRender.begin(), m_NormalHPRender.end(),
		[](ActionGame::NormalEnemyHPRenderPtr& obj1, ActionGame::NormalEnemyHPRenderPtr& obj2)
		{
			return obj1->GetViewPosition().z > obj2->GetViewPosition().z;
		});
}

void ActionGame::NPCHPRenderManager::Add(const NormalEnemyHPRenderPtr& render)
{
	m_NormalHPRender.push_back(render);
}

void ActionGame::NPCHPRenderManager::Add(const BossHPRenderPtr& render)
{
	m_BossHPRender.push_back(render);
}
