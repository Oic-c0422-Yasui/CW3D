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

	//�e�N�X�`�������łɓǂݍ��܂�Ă���Ȃ�A���\�[�X�����o��
	if (ResourcePtrManager<CTexture>::GetInstance().IsContainResource("Texture", "LoadingTex"))
	{
		m_BackTex = ResourcePtrManager<CTexture>::GetInstance().GetResource("Texture", "LoadingTex");
	}
	else
	{
		//�e�N�X�`���ǂݍ���
		if (!m_BackTex->Load("BackImage/LoadingBack.png"))
		{
			return false;
		}
		//�e�N�X�`����o�^
		ResourcePtrManager<CTexture>::GetInstance().AddResource("Texture", "LoadingTex", m_BackTex);
	}

	font_->Create(50, "�l�r �S�V�b�N");

	//���[�h����V�[�������邩�m�F
	assert(m_LoadingScene);

	//�V�[�������[�h
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
	//�V�[���̃��[�h������������
	if (m_LoadThread.IsComplete())
	{
		//���[�h�����V�[���֑J�ڂ���
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
	//��ʂ̃T�C�Y
	float width = g_pGraphics->GetTargetWidth();
	float height = g_pGraphics->GetTargetHeight();
	//�w�i
	CRectangle rect(0, 0, width, height);
	m_BackTex->Render(rect);

	//���[�f�B���O�e�L�X�g
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
