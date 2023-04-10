#include "NPCHPRenderManager.h"
#include "RegistMessageServiceDefine.h"



ActionGame::CNPCHPRenderManager::CNPCHPRenderManager()
	: normalHPRender_()
	, bossHPRender_()
	, isShow_(true)
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
	isShow_ = true;
}

void ActionGame::CNPCHPRenderManager::Render()
{
	if (!isShow_)
	{
		return;
	}
	//敵HPバーの描画入れ替え
	Sort();

	for (auto normal : normalHPRender_)
	{
		normal->Render();
	}
	
}

void ActionGame::CNPCHPRenderManager::Render2D()
{
	if (!isShow_)
	{
		return;
	}
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
	//HPバーの描画入れ替え
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

void ActionGame::CNPCHPRenderManager::RegistSendMessage()
{
	const auto& message = RegistMessageService::GetService();
	//メッセージ登録
	//UI表示メッセージ
	message->Regist(UI_Visible,
		[&]() {VisibleUI(); });
	//UI非表示メッセージ
	message->Regist(UI_Disable,
		[&]() {DisableUI(); });
}

void ActionGame::CNPCHPRenderManager::VisibleUI()
{
	isShow_ = true;
}

void ActionGame::CNPCHPRenderManager::DisableUI()
{
	isShow_ = false;
}