#include "TitleScene.h"



ActionGame::CTitleScene::CTitleScene()
	: m_BackTexture(std::make_shared<CTexture>())
	, m_Font(std::make_shared<CFont>())
{
}

ActionGame::CTitleScene::~CTitleScene()
{
}

bool ActionGame::CTitleScene::Load()
{
	if (!m_BackTexture->Load("BackImage/TitleBack.jpg"))
	{
		return false;
	}
	m_Font->Create(150, "ＭＳ ゴシック");

	return true;
}

void ActionGame::CTitleScene::Initialize()
{
}

void ActionGame::CTitleScene::Update()
{
	if (InputManagerInstance.GetInput(0)->IsPush(INPUT_KEY_ENTER))
	{
		ActionGame::ServiceLocator<ActionGame::ISceneChanger>::GetService()->ChangeScene(SCENE_GAME,true);
	}
}

void ActionGame::CTitleScene::Render()
{
}

void ActionGame::CTitleScene::RenderDebug()
{
}

void ActionGame::CTitleScene::Render2D()
{
	float width = g_pGraphics->GetTargetWidth();
	float height = g_pGraphics->GetTargetHeight();
	CRectangle rect(0, 0, width, height);
	m_BackTexture->Render(rect);
	m_Font->CalculateStringRect(0, 0, "アクションげーーーむ", rect);
	m_Font->RenderString(width * 0.5f - (rect.GetWidth() * 0.5f), height * 0.5f - (rect.GetHeight() * 0.5f),MOF_XRGB(255,0,0), "アクションげーーーむ");
}

void ActionGame::CTitleScene::Render2DDebug()
{
}

void ActionGame::CTitleScene::Release()
{
	m_BackTexture.reset();
	m_Font.reset();
}
