#include "TitleScene.h"



Scene::TitleScene::TitleScene()
	: m_BackTexture(std::make_shared<CTexture>())
	, m_TitleLogoFont()
	, m_TextFont()
{
}

Scene::TitleScene::~TitleScene()
{
}

bool Scene::TitleScene::Load()
{
	if (!m_BackTexture->Load("BackImage/TitleBack.png"))
	{
		return false;
	}
	m_TitleLogoFont.Create(150, "ＭＳ ゴシック");
	m_TextFont.Create(50, "ＭＳ ゴシック");
	return true;
}

void Scene::TitleScene::Initialize()
{
}

void Scene::TitleScene::Update()
{
	//キー入力
	auto input = InputManagerInstance.GetInput(0);

	if (input->IsPush(INPUT_KEY_ENTER))
	{
		//ゲームシーンへ遷移
		SceneChangeService::GetService()->ChangeScene(SCENENO::GAME,true);
	}
	else if (InputManagerInstance.GetInput(0)->IsPush(INPUT_KEY_CANCEL))
	{
		//ゲーム終了
		PostQuitMessage(0);
	}
}

void Scene::TitleScene::Render()
{
}

void Scene::TitleScene::RenderDebug()
{
}

void Scene::TitleScene::Render2D()
{
	//画面のサイズ
	float width = g_pGraphics->GetTargetWidth();
	float height = g_pGraphics->GetTargetHeight();
	//背景
	CRectangle rect(0, 0, width, height);
	m_BackTexture->Render(rect);

	//タイトルロゴ
	m_TitleLogoFont.CalculateStringRect(0, 0, "アクションげーーーむ", rect);
	m_TitleLogoFont.RenderString(width * 0.5f - (rect.GetWidth() * 0.5f), height * 0.2f ,MOF_XRGB(0,0,0), "アクションげーーーむ");

	//説明
	m_TextFont.CalculateStringRect(0, 0, "Start：Z Key", rect);
	m_TextFont.RenderString(width * 0.5f - (rect.GetWidth() * 0.5f), height * 0.7f, MOF_XRGB(0, 0, 0), "Start：Z Key");
	m_TextFont.CalculateStringRect(0, 0, "End：X Key", rect);
	m_TextFont.RenderString(width * 0.5f - (rect.GetWidth() * 0.5f), height * 0.78f, MOF_XRGB(0, 0, 0), "End：X Key");
}

void Scene::TitleScene::Render2DDebug()
{
}

void Scene::TitleScene::Release()
{
	m_BackTexture.reset();
	m_TitleLogoFont.Release();
	m_TextFont.Release();
}
