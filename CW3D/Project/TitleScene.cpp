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

	//�f�o�C�X�ύX�ɂ��UI�ύX���b�Z�[�W�o�^
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
	//�L�[����
	auto input = InputManagerInstance.GetInput(0);

	if (input->IsPush(INPUT_KEY_ENTER))
	{
		//�t�F�[�h
		constexpr float time = 0.5f;
		auto sceneEffect = std::make_shared<Scene::SceneChangeFade>(time, time, time);
		//�Q�[���V�[���֑J��
		SceneChangeService::GetService()->ChangeScene(SCENENO::GAME, sceneEffect,true);
	}
	else if (input->IsPush(INPUT_KEY_CANCEL))
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
	titleLogoFont_.CalculateStringRect(0, 0, "Go�I Action�I", rect);
	titleLogoFont_.RenderString(width * 0.2f, height * 0.2f , "Go�I Action�I");
	
	//�{�^��
	textFont_.CalculateStringRect(width * 0.5f, height * 0.7f, "START�F", rect);
	rect += CRectangle(rect.GetWidth() * -0.5f, 0, rect.GetWidth() * -0.5f, 0);
	textFont_.RenderString(rect.Left, rect.Top, "START�F");
	textFont_.RenderString(rect.Right, rect.Top, startButtonStr_);

	textFont_.CalculateStringRect(width * 0.5f, height * 0.78f, "END�F", rect);
	rect += CRectangle(rect.GetWidth() * -0.5f, 0, rect.GetWidth() * -0.5f, 0);
	textFont_.RenderString(rect.Left, rect.Top, "END�F");
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
	startButtonStr_ = "Z�L�[";
	endButtonStr_ = "X�L�[";
}

void Scene::CTitleScene::ChangeControllerUI()
{
	startButtonStr_ = "A�{�^��";
	endButtonStr_ = "B�{�^��";
}