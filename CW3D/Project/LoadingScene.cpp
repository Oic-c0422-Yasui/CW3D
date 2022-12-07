#include "LoadingScene.h"
#include "ServiceLocator.h"

ActionGame::LoadingScene::LoadingScene(ScenePtr loadingScene)
	: m_LoadingScene(loadingScene)
	, m_LoadThread()
	, m_BackTex(std::make_shared<CTexture>())
{
}

ActionGame::LoadingScene::~LoadingScene()
{
	Release();
}

bool ActionGame::LoadingScene::Load()
{

	//�e�N�X�`�������łɓǂݍ��܂�Ă���Ȃ�
	if (ActionGame::ResourcePtrManager<CTexture>::GetInstance().IsContainResource("Texture", "LoadingTex"))
	{
		m_BackTex = ActionGame::ResourcePtrManager<CTexture>::GetInstance().GetResource("Texture", "LoadingTex");
	}
	else
	{
		//�e�N�X�`���ǂݍ���
		if (!m_BackTex->Load("BackImage/LoadingBack.jpg"))
		{
			return false;
		}
		//�e�N�X�`����o�^
		ActionGame::ResourcePtrManager<CTexture>::GetInstance().AddResource("Texture", "LoadingTex", m_BackTex);
	}

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

void ActionGame::LoadingScene::Initialize()
{
}

void ActionGame::LoadingScene::Update()
{
	if (m_LoadThread.IsComplete())
	{
		ActionGame::ServiceLocator<ActionGame::ISceneChanger>::GetService()->ChangeScene(m_LoadingScene);
	}
}

void ActionGame::LoadingScene::Render()
{
	CRectangle rect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight());

	m_BackTex->Render(rect);
}

void ActionGame::LoadingScene::RenderDebug()
{
}

void ActionGame::LoadingScene::Render2D()
{
}

void ActionGame::LoadingScene::Render2DDebug()
{
}

void ActionGame::LoadingScene::Release()
{
	if (m_BackTex)
	{
		m_BackTex.reset();
	}
	if (m_LoadingScene)
	{
		m_LoadingScene.reset();
	}
}
