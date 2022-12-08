#include "LoadingScene.h"
#include "ServiceLocator.h"

ActionGame::LoadingScene::LoadingScene(ScenePtr loadingScene)
	: m_LoadingScene(loadingScene)
	, m_LoadThread()
	, m_BackTex(std::make_shared<CTexture>())
	, m_Font(std::make_shared<CFont>())
{
}

ActionGame::LoadingScene::~LoadingScene()
{
	Release();
}

bool ActionGame::LoadingScene::Load()
{

	//テクスチャがすでに読み込まれているなら、リソースを取り出す
	if (ActionGame::ResourcePtrManager<CTexture>::GetInstance().IsContainResource("Texture", "LoadingTex"))
	{
		m_BackTex = ActionGame::ResourcePtrManager<CTexture>::GetInstance().GetResource("Texture", "LoadingTex");
	}
	else
	{
		//テクスチャ読み込み
		if (!m_BackTex->Load("BackImage/LoadingBack.png"))
		{
			return false;
		}
		//テクスチャを登録
		ActionGame::ResourcePtrManager<CTexture>::GetInstance().AddResource("Texture", "LoadingTex", m_BackTex);
	}

	m_Font->Create(50, "ＭＳ ゴシック");

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
	//シーンのロードが完了したら
	if (m_LoadThread.IsComplete())
	{
		//ロードしたシーンへ遷移する
		ActionGame::ServiceLocator<ActionGame::ISceneChanger>::GetService()->ChangeScene(m_LoadingScene);
	}
}

void ActionGame::LoadingScene::Render()
{
	
}

void ActionGame::LoadingScene::RenderDebug()
{
}

void ActionGame::LoadingScene::Render2D()
{
	//画面のサイズ
	float width = g_pGraphics->GetTargetWidth();
	float height = g_pGraphics->GetTargetHeight();
	//背景
	CRectangle rect(0, 0, width, height);
	m_BackTex->Render(rect);

	//ローディングテキスト
	m_Font->CalculateStringRect(0, 0, "NowLoading...", rect);
	m_Font->RenderString(width - (rect.GetWidth() + 200), height * 0.9f, "NowLoading...");
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
	if (m_Font)
	{
		m_Font.reset();
	}
	if (m_LoadingScene)
	{
		m_LoadingScene.reset();
	}
}
