#include "LoadingScene.h"
#include "ServiceLocator.h"

Scene::LoadingScene::LoadingScene(ScenePtr loadingScene)
	: m_LoadingScene(loadingScene)
	, m_LoadThread()
	, m_BackTex(std::make_shared<CTexture>())
	, font_(std::make_shared<CFont>())
{
}

Scene::LoadingScene::~LoadingScene()
{
	Release();
}

bool Scene::LoadingScene::Load()
{

	//テクスチャがすでに読み込まれているなら、リソースを取り出す
	if (ResourcePtrManager<CTexture>::GetInstance().IsContainResource("Texture", "LoadingTex"))
	{
		m_BackTex = ResourcePtrManager<CTexture>::GetInstance().GetResource("Texture", "LoadingTex");
	}
	else
	{
		//テクスチャ読み込み
		if (!m_BackTex->Load("BackImage/LoadingBack.png"))
		{
			return false;
		}
		//テクスチャを登録
		ResourcePtrManager<CTexture>::GetInstance().AddResource("Texture", "LoadingTex", m_BackTex);
	}

	font_->Create(50, "ＭＳ ゴシック");

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

void Scene::LoadingScene::Initialize()
{
}

void Scene::LoadingScene::Update()
{
	//シーンのロードが完了したら
	if (m_LoadThread.IsComplete())
	{
		//ロードしたシーンへ遷移する
		ActionGame::ServiceLocator<Scene::ISceneChanger>::GetService()->ChangeScene(m_LoadingScene);
	}
}

void Scene::LoadingScene::Render()
{
	
}

void Scene::LoadingScene::RenderDebug()
{
}

void Scene::LoadingScene::Render2D()
{
	//画面のサイズ
	float width = g_pGraphics->GetTargetWidth();
	float height = g_pGraphics->GetTargetHeight();
	//背景
	CRectangle rect(0, 0, width, height);
	m_BackTex->Render(rect);

	//ローディングテキスト
	font_->CalculateStringRect(0, 0, "NowLoading...", rect);
	font_->RenderString(width - (rect.GetWidth() + 200), height * 0.9f, "NowLoading...");
}

void Scene::LoadingScene::Render2DDebug()
{
}

void Scene::LoadingScene::Release()
{
	if (m_BackTex)
	{
		m_BackTex.reset();
	}
	if (font_)
	{
		font_.reset();
	}
	if (m_LoadingScene)
	{
		m_LoadingScene.reset();
	}
}
