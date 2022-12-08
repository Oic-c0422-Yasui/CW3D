#include "SceneManager.h"
#include "LoadingScene.h"

using namespace ActionGame;



SceneManager::SceneManager()
	: m_DebugFlg(false)
	, m_Scene()
{
}

SceneManager::~SceneManager()
{

}

void ActionGame::SceneManager::RegistScene(tag_SCENENO sceneNo, SceneCreatorPtr creator)
{
	m_SceneMap[sceneNo] = std::move(creator);
}

bool ActionGame::SceneManager::ChangeScene(tag_SCENENO sceneNo)
{
	//�Â��V�[����j��
	if (m_Scene)
	{
		m_Scene->Release();
	}

	//�V�[���쐬
	ScenePtr temp = m_SceneMap[sceneNo]->Create();
	temp->Load();
	temp->Initialize();

	m_Scene = temp;

	return true;
}

bool ActionGame::SceneManager::ChangeScene(const ScenePtr& scene)
{
	auto temp = scene;
	//�Â��V�[����j��
	if (m_Scene)
	{
		m_Scene->Release();
	}
	m_Scene = temp;
	return true;
}

void ActionGame::SceneManager::InitializeScene(SceneChangeEffectPtr effect)
{
}

bool ActionGame::SceneManager::ChangeScene(tag_SCENENO sceneNo, bool isLoading)
{
	//���[�h�����܂Ȃ��Ȃ畁�ʂɃV�[���؂�ւ�
	if (!isLoading)
	{
		return ChangeScene(sceneNo);
	}

	//�V�[���쐬
	ScenePtr temp = m_SceneMap[sceneNo]->Create();

	//�Â��V�[����j��
	if (m_Scene)
	{
		m_Scene->Release();
	}

	//���[�f�B���O�V�[���쐬
	auto loading = std::make_shared<ActionGame::LoadingScene>(temp);
	loading->Load();
	loading->Initialize();

	m_Scene = loading;

	return true;
}


bool SceneManager::Load()
{

	return true;
}

void SceneManager::Initialize()
{
	m_UpdateTask.DeleteAllTaskImmediate();
	//�^�X�N�o�^
	RegisterTask();
}

void SceneManager::Update()
{
	//�f�o�b�O�؂�ւ�
	if (g_pInput->IsKeyPush(MOFKEY_F1))
	{
		m_DebugFlg = m_DebugFlg ? false : true;
		if (m_DebugFlg)
		{
			//�f�o�b�O�^�X�N�o�^
			RegisterDebugTask();
		}
		else
		{
			//�f�o�b�O�^�X�N�폜
			DeleteDebugTask();
		}
	}

	//�X�V�^�X�N
	m_UpdateTask.Excution();

	
}

void SceneManager::Render()
{
	
	if (m_Scene)
	{
		g_pGraphics->SetDepthEnable(TRUE);
		m_Scene->Render();


		if (m_DebugFlg)
		{
			m_Scene->RenderDebug();
		}

		g_pGraphics->SetDepthEnable(FALSE);

		m_Scene->Render2D();

		if (m_DebugFlg)
		{
			m_Scene->Render2DDebug();
		}

	}
}

void SceneManager::Release()
{
	if (m_Scene)
	{
		m_Scene->Release();
		m_Scene.reset();
	}
}


void ActionGame::SceneManager::RegisterTask()
{
	//�X�V�^�X�N
	RegisterUpdateTask();
}

void ActionGame::SceneManager::RegisterUpdateTask()
{
	/////////////////////////////////////////////////////
	///			�X�V�^�X�N
	/////////////////////////////////////////////////////
	m_UpdateTask.AddTask("UpdateScene", TASK_MAIN1,
		[&]()
			{
				if (m_Scene)
				{
					m_Scene->Update();
				}
			}
		);
	
}

void ActionGame::SceneManager::RegisterDebugTask()
{
	/////////////////////////////////////////////////////
	///			�f�o�b�O�^�X�N
	/////////////////////////////////////////////////////
	m_UpdateTask.AddTask("UpdateDebug", TASK_MAIN1,
		[&]()
			{
				//�V�[���J��
				if (g_pInput->IsKeyHold(MOFKEY_LCONTROL))
				{
					if (g_pInput->IsKeyPush(MOFKEY_1))
					{
						ChangeScene(SCENE_TITLE);
					}
					else if (g_pInput->IsKeyPush(MOFKEY_2))
					{
						ChangeScene(SCENE_GAME);
					}
				}
			}
		);
}

void ActionGame::SceneManager::DeleteDebugTask()
{
	m_UpdateTask.DeleteTask("UpdateDebug");
}
