#include "TitleScene.h"



Scene::CTitleScene::CTitleScene()
	: backTexture_(std::make_shared<CTexture>())
	, titleLogoFont_()
	, textFont_()
{
}

Scene::CTitleScene::~CTitleScene()
{

}

bool Scene::CTitleScene::Load()
{
	if (!backTexture_->Load("BackImage/TitleBack.png"))
	{
		return false;
	}
	titleLogoFont_.Create(150, "ＭＳ ゴシック");
	textFont_.Create(50, "ＭＳ ゴシック");

	return true;
}

void Scene::CTitleScene::Initialize()
{
}

void Scene::CTitleScene::Update()
{
	//キー入力
	auto input = InputManagerInstance.GetInput(0);

	if (input->IsPush(INPUT_KEY_ENTER))
	{
		//フェード
		const float time = 0.5f;
		auto sceneEffect = std::make_shared<Scene::SceneChangeFade>(time, time, time);
		//ゲームシーンへ遷移
		SceneChangeService::GetService()->ChangeScene(SCENENO::GAME, sceneEffect,true);
	}
	else if (InputManagerInstance.GetInput(0)->IsPush(INPUT_KEY_CANCEL))
	{
		//ゲーム終了
		PostQuitMessage(0);
	}
}

void Scene::CTitleScene::Render()
{
}

void Scene::CTitleScene::RenderDebug()
{
}

void Scene::CTitleScene::Render2D()
{
	//画面のサイズ
	float width = g_pGraphics->GetTargetWidth();
	float height = g_pGraphics->GetTargetHeight();
	//背景
	CRectangle rect(0, 0, width, height);
	backTexture_->Render(rect);

	//タイトルロゴ
	titleLogoFont_.CalculateStringRect(0, 0, "アクションげーーーむ", rect);
	titleLogoFont_.RenderString(width * 0.5f - (rect.GetWidth() * 0.5f), height * 0.2f , "アクションげーーーむ");

	//説明
	textFont_.CalculateStringRect(0, 0, "Start：Z Key", rect);
	textFont_.RenderString(width * 0.5f - (rect.GetWidth() * 0.5f), height * 0.7f, "Start：Z Key");
	textFont_.CalculateStringRect(0, 0, "End：X Key", rect);
	textFont_.RenderString(width * 0.5f - (rect.GetWidth() * 0.5f), height * 0.78f, "End：X Key");
}

void Scene::CTitleScene::Render2DDebug()
{
}

void Scene::CTitleScene::Release()
{
	if (backTexture_)
	{
		backTexture_.reset();
	}
	titleLogoFont_.Release();
	textFont_.Release();
}
