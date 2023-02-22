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
	m_TitleLogoFont.Create(150, "�l�r �S�V�b�N");
	m_TextFont.Create(50, "�l�r �S�V�b�N");
	return true;
}

void Scene::TitleScene::Initialize()
{
}

void Scene::TitleScene::Update()
{
	//�L�[����
	auto input = InputManagerInstance.GetInput(0);

	if (input->IsPush(INPUT_KEY_ENTER))
	{
		//�Q�[���V�[���֑J��
		SceneChangeService::GetService()->ChangeScene(SCENENO::GAME,true);
	}
	else if (InputManagerInstance.GetInput(0)->IsPush(INPUT_KEY_CANCEL))
	{
		//�Q�[���I��
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
	//��ʂ̃T�C�Y
	float width = g_pGraphics->GetTargetWidth();
	float height = g_pGraphics->GetTargetHeight();
	//�w�i
	CRectangle rect(0, 0, width, height);
	m_BackTexture->Render(rect);

	//�^�C�g�����S
	m_TitleLogoFont.CalculateStringRect(0, 0, "�A�N�V�������[�[�[��", rect);
	m_TitleLogoFont.RenderString(width * 0.5f - (rect.GetWidth() * 0.5f), height * 0.2f ,MOF_XRGB(0,0,0), "�A�N�V�������[�[�[��");

	//����
	m_TextFont.CalculateStringRect(0, 0, "Start�FZ Key", rect);
	m_TextFont.RenderString(width * 0.5f - (rect.GetWidth() * 0.5f), height * 0.7f, MOF_XRGB(0, 0, 0), "Start�FZ Key");
	m_TextFont.CalculateStringRect(0, 0, "End�FX Key", rect);
	m_TextFont.RenderString(width * 0.5f - (rect.GetWidth() * 0.5f), height * 0.78f, MOF_XRGB(0, 0, 0), "End�FX Key");
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
