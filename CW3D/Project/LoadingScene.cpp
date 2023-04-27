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

	//���\�[�X�̖��O��`
	auto tag = "Texture";
	auto name = "LoadingTex";
	//�e�N�X�`�������łɓǂݍ��܂�Ă���Ȃ�A���\�[�X�����o��
	if (ResourcePtrManager<CTexture>::GetInstance().IsContainResource(tag, name))
	{
		backTexture_ = ResourcePtrManager<CTexture>::GetInstance().GetResource(tag, name);
	}
	else
	{
		//�e�N�X�`���ǂݍ���
		if (!backTexture_->Load("BackImage/LoadingBack.png"))
		{
			return false;
		}
		//�e�N�X�`����o�^
		ResourcePtrManager<CTexture>::GetInstance().AddResource(tag, name, backTexture_);
	}

	font_->Create(50, "�l�r �S�V�b�N");

	//���[�h����V�[�������邩�m�F
	assert(loadingScene_);

	//�V�[�������[�h
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
	//�V�[���̃��[�h������������
	if (loadThread_.IsComplete())
	{
		//�t�F�[�h
		float time = 0.5f;
		auto sceneEffect = std::make_shared<Scene::SceneChangeFade>(time, time, time);
		//���[�h�����V�[���֑J�ڂ���
		SceneChangeService::GetService()->ChangeScene(loadingScene_, sceneEffect);
		return;
	}
	timer_.Update();

	if (timer_.IsAchieve())
	{
		//���[�h�A�j���[�V�����̐�
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

		//�^�C�}�[���Z�b�g
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
	//��ʂ̃T�C�Y
	float width = g_pGraphics->GetTargetWidth();
	float height = g_pGraphics->GetTargetHeight();
	//�w�i
	CRectangle rect(0, 0, width, height);
	backTexture_->Render(rect);

	//���[�f�B���O�e�L�X�g
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
