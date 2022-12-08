#include "LoadingScene.h"
#include "ServiceLocator.h"

ActionGame::LoadingScene::LoadingScene(ScenePtr loadingScene)
	: m_LoadingScene(loadingScene)
	, m_LoadThread()
	, m_BackTex(std::make_shared<CTexture>())
	, m_Font(std::make_shared<CFont>())
{
}

ActionGame::LoadingScene::~LoadingScene()
{
	Release();
}

bool ActionGame::LoadingScene::Load()
{

	//�e�N�X�`�������łɓǂݍ��܂�Ă���Ȃ�A���\�[�X�����o��
	if (ActionGame::ResourcePtrManager<CTexture>::GetInstance().IsContainResource("Texture", "LoadingTex"))
	{
		m_BackTex = ActionGame::ResourcePtrManager<CTexture>::GetInstance().GetResource("Texture", "LoadingTex");
	}
	else
	{
		//�e�N�X�`���ǂݍ���
		if (!m_BackTex->Load("BackImage/LoadingBack.png"))
		{
			return false;
		}
		//�e�N�X�`����o�^
		ActionGame::ResourcePtrManager<CTexture>::GetInstance().AddResource("Texture", "LoadingTex", m_BackTex);
	}

	m_Font->Create(50, "�l�r �S�V�b�N");

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
	//�V�[���̃��[�h������������
	if (m_LoadThread.IsComplete())
	{
		//���[�h�����V�[���֑J�ڂ���
		ActionGame::ServiceLocator<ActionGame::ISceneChanger>::GetService()->ChangeScene(m_LoadingScene);
	}
}

void ActionGame::LoadingScene::Render()
{
	
}

void ActionGame::LoadingScene::RenderDebug()
{
}

void ActionGame::LoadingScene::Render2D()
{
	//��ʂ̃T�C�Y
	float width = g_pGraphics->GetTargetWidth();
	float height = g_pGraphics->GetTargetHeight();
	//�w�i
	CRectangle rect(0, 0, width, height);
	m_BackTex->Render(rect);

	//���[�f�B���O�e�L�X�g
	m_Font->CalculateStringRect(0, 0, "NowLoading...", rect);
	m_Font->RenderString(width - (rect.GetWidth() + 200), height * 0.9f, "NowLoading...");
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
	if (m_Font)
	{
		m_Font.reset();
	}
	if (m_LoadingScene)
	{
		m_LoadingScene.reset();
	}
}
