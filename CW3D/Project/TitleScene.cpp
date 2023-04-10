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
	titleLogoFont_.Create(150, "�l�r �S�V�b�N");
	textFont_.Create(50, "�l�r �S�V�b�N");

	return true;
}

void Scene::CTitleScene::Initialize()
{
}

void Scene::CTitleScene::Update()
{
	//�L�[����
	auto input = InputManagerInstance.GetInput(0);

	if (input->IsPush(INPUT_KEY_ENTER))
	{
		//�t�F�[�h
		const float time = 0.5f;
		auto sceneEffect = std::make_shared<Scene::SceneChangeFade>(time, time, time);
		//�Q�[���V�[���֑J��
		SceneChangeService::GetService()->ChangeScene(SCENENO::GAME, sceneEffect,true);
	}
	else if (InputManagerInstance.GetInput(0)->IsPush(INPUT_KEY_CANCEL))
	{
		//�Q�[���I��
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
	//��ʂ̃T�C�Y
	float width = g_pGraphics->GetTargetWidth();
	float height = g_pGraphics->GetTargetHeight();
	//�w�i
	CRectangle rect(0, 0, width, height);
	backTexture_->Render(rect);

	//�^�C�g�����S
	titleLogoFont_.CalculateStringRect(0, 0, "�A�N�V�������[�[�[��", rect);
	titleLogoFont_.RenderString(width * 0.5f - (rect.GetWidth() * 0.5f), height * 0.2f , "�A�N�V�������[�[�[��");

	//����
	textFont_.CalculateStringRect(0, 0, "Start�FZ Key", rect);
	textFont_.RenderString(width * 0.5f - (rect.GetWidth() * 0.5f), height * 0.7f, "Start�FZ Key");
	textFont_.CalculateStringRect(0, 0, "End�FX Key", rect);
	textFont_.RenderString(width * 0.5f - (rect.GetWidth() * 0.5f), height * 0.78f, "End�FX Key");
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
