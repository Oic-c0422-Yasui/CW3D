#include "TitleScene.h"
#include "RegistMessageServiceDefine.h"



Scene::CTitleScene::CTitleScene()
	: backTexture_(std::make_shared<CTexture>())
	, titleLogoFont_()
	, textFont_()
	, startButtonStr_(nullptr)
	, endButtonStr_(nullptr)
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
	titleLogoFont_.Create(200, "M PLUS 1");
	titleLogoFont_.SetBold(60);
	textFont_.Create(50, "M PLUS 1");

	auto input = InputManagerInstance.GetInput(0);
	switch (input->GetDeviceType())
	{
	case GameDevice::KeyBoardAndMouse:
		ChangeKeyBoardUI();
		break;
	case GameDevice::Controller:
		ChangeControllerUI();
		break;
	default:
		break;
	}

	//デバイス変更によるUI変更メッセージ登録
	const auto& message = RegistMessageService::GetService();
	message->Regist(ChangeDevice_KeyBoard,
		[this]() {ChangeKeyBoardUI(); });
	message->Regist(ChangeDevice_Controller,
		[this]() {ChangeControllerUI(); });

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
		constexpr float time = 0.5f;
		auto sceneEffect = std::make_shared<Scene::SceneChangeFade>(time, time, time);
		//ゲームシーンへ遷移
		SceneChangeService::GetService()->ChangeScene(SCENENO::GAME, sceneEffect,true);
	}
	else if (input->IsPush(INPUT_KEY_CANCEL))
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
	titleLogoFont_.CalculateStringRect(0, 0, "Go！ Action！", rect);
	titleLogoFont_.RenderString(width * 0.2f, height * 0.2f , "Go！ Action！");
	
	//ボタン
	textFont_.CalculateStringRect(width * 0.5f, height * 0.7f, "START：", rect);
	rect += CRectangle(rect.GetWidth() * -0.5f, 0, rect.GetWidth() * -0.5f, 0);
	textFont_.RenderString(rect.Left, rect.Top, "START：");
	textFont_.RenderString(rect.Right, rect.Top, startButtonStr_);

	textFont_.CalculateStringRect(width * 0.5f, height * 0.78f, "END：", rect);
	rect += CRectangle(rect.GetWidth() * -0.5f, 0, rect.GetWidth() * -0.5f, 0);
	textFont_.RenderString(rect.Left, rect.Top, "END：");
	textFont_.RenderString(rect.Right, rect.Top, endButtonStr_);
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

void Scene::CTitleScene::ChangeKeyBoardUI()
{
	startButtonStr_ = "Zキー";
	endButtonStr_ = "Xキー";
}

void Scene::CTitleScene::ChangeControllerUI()
{
	startButtonStr_ = "Aボタン";
	endButtonStr_ = "Bボタン";
}