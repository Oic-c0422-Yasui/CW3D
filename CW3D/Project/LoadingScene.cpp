#include "LoadingScene.h"
#include "ServiceLocator.h"

ActionGame::LoadingScene::LoadingScene(ScenePtr loadingScene)
	: m_LoadingScene(loadingScene)
	, m_LoadThread()
	, m_BackTex(std::make_shared<CTexture>())
{
}

ActionGame::LoadingScene::~LoadingScene()
{
	Release();
}

bool ActionGame::LoadingScene::Load()
{

	//テクスチャがすでに読み込まれているなら
	if (ActionGame::ResourcePtrManager<CTexture>::GetInstance().IsContainResource("Texture", "LoadingTex"))
	{
		m_BackTex = ActionGame::ResourcePtrManager<CTexture>::GetInstance().GetResource("Texture", "LoadingTex");
	}
	else
	{
		//テクスチャ読み込み
		if (!m_BackTex->Load("BackImage/LoadingBack.jpg"))
		{
			return false;
		}
		//テクスチャを登録
		ActionGame::ResourcePtrManager<CTexture>::GetInstance().AddResource("Texture", "LoadingTex", m_BackTex);
	}

	//ロードするシーンがあるか確認
	assert(m_LoadingScene);

	//シーンをロード
	m_LoadThread.Create([this]()
								{
									m_LoadingScene->Load();
									m_LoadingScene->Initialize();
									return true;
								});

	

	return true;
}

void ActionGame::LoadingScene::Initialize()
{
}

void ActionGame::LoadingScene::Update()
{
	if (m_LoadThread.IsComplete())
	{
		ActionGame::ServiceLocator<ActionGame::ISceneChanger>::GetService()->ChangeScene(m_LoadingScene);
	}
}

void ActionGame::LoadingScene::Render()
{
	CRectangle rect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight());

	m_BackTex->Render(rect);
}

void ActionGame::LoadingScene::RenderDebug()
{
}

void ActionGame::LoadingScene::Render2D()
{
}

void ActionGame::LoadingScene::Render2DDebug()
{
}

void ActionGame::LoadingScene::Release()
{
	if (m_BackTex)
	{
		m_BackTex.reset();
	}
	if (m_LoadingScene)
	{
		m_LoadingScene.reset();
	}
}
