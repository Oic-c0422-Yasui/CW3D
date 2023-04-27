#include "LoadingScene.h"
#include "SceneServiceDefine.h"
#include "SceneChangeFade.h"


Scene::CLoadingScene::CLoadingScene(ScenePtr loadingScene)
	: loadingScene_(loadingScene)
	, loadThread_()
	, backTexture_(std::make_shared<CTexture>())
	, font_(std::make_shared<CFont>())
	, loadingStr_()
	, currentAnimCount_(0)
	, timer_()
{
}

Scene::CLoadingScene::~CLoadingScene()
{
}

bool Scene::CLoadingScene::Load()
{

	//リソースの名前定義
	auto tag = "Texture";
	auto name = "LoadingTex";
	//テクスチャがすでに読み込まれているなら、リソースを取り出す
	if (ResourcePtrManager<CTexture>::GetInstance().IsContainResource(tag, name))
	{
		backTexture_ = ResourcePtrManager<CTexture>::GetInstance().GetResource(tag, name);
	}
	else
	{
		//テクスチャ読み込み
		if (!backTexture_->Load("BackImage/LoadingBack.png"))
		{
			return false;
		}
		//テクスチャを登録
		ResourcePtrManager<CTexture>::GetInstance().AddResource(tag, name, backTexture_);
	}

	font_->Create(50, "ＭＳ ゴシック");

	//ロードするシーンがあるか確認
	assert(loadingScene_);

	//シーンをロード
	loadThread_.Create([this]()
								{
									loadingScene_->Load();
									loadingScene_->Initialize();
									return true;
								});

	return true;
}

void Scene::CLoadingScene::Initialize()
{
	const float animTime = 0.3f;
	currentAnimCount_ = 0;
	loadingStr_ = "";
	timer_.Start(animTime);
}

void Scene::CLoadingScene::Update()
{
	//シーンのロードが完了したら
	if (loadThread_.IsComplete())
	{
		//フェード
		float time = 0.5f;
		auto sceneEffect = std::make_shared<Scene::SceneChangeFade>(time, time, time);
		//ロードしたシーンへ遷移する
		SceneChangeService::GetService()->ChangeScene(loadingScene_, sceneEffect);
		return;
	}
	timer_.Update();

	if (timer_.IsAchieve())
	{
		//ロードアニメーションの数
		const BYTE animCount = 3;
		if (animCount > currentAnimCount_)
		{
			currentAnimCount_++;
			loadingStr_.push_back('.');
		}
		else
		{
			currentAnimCount_ = 0;
			loadingStr_ = "";
		}

		//タイマーリセット
		timer_.Reset();
	}
	
}

void Scene::CLoadingScene::Render()
{
	
}

void Scene::CLoadingScene::RenderDebug()
{
}

void Scene::CLoadingScene::Render2D()
{
	//画面のサイズ
	float width = g_pGraphics->GetTargetWidth();
	float height = g_pGraphics->GetTargetHeight();
	//背景
	CRectangle rect(0, 0, width, height);
	backTexture_->Render(rect);

	//ローディングテキスト
	font_->CalculateStringRect(0, 0, "NowLoading", rect);
	font_->RenderString(width - (rect.GetWidth() + 200), height * 0.9f, "NowLoading");
	font_->RenderString(width - 200, height * 0.9f, loadingStr_.c_str());

}

void Scene::CLoadingScene::Render2DDebug()
{
}

void Scene::CLoadingScene::Release()
{
	if (backTexture_)
	{
		backTexture_.reset();
	}
	if (font_)
	{
		font_.reset();
	}
	if (loadingScene_)
	{
		loadingScene_.reset();
	}
}
