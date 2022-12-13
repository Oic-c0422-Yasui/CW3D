#include "SceneManager.h"
#include "LoadingScene.h"

using namespace ActionGame;



SceneManager::SceneManager()
	: m_DebugFlg(false)
	, m_SceneInitFlg(false)
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
	m_SceneEffect = effect;
	m_SceneInitFlg = false;
	RegisterSceneChangeEffectTask();
	
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
	m_RenderTask.DeleteAllTaskImmediate();
	m_Render2DTask.DeleteAllTaskImmediate();
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
	
	//�[�x�o�b�t�@�L����
	g_pGraphics->SetDepthEnable(TRUE);
	if (m_DebugFlg)
	{
		int a;
		a = 1;
	}
	//�`��^�X�N
	m_RenderTask.Excution();

	//�[�x�o�b�t�@������
	g_pGraphics->SetDepthEnable(FALSE);

	//�`��^�X�N
	m_Render2DTask.Excution();
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
	//�`��^�X�N
	RegisterRenderTask();
	//2D�`��^�X�N
	RegisterRender2DTask();
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

void ActionGame::SceneManager::RegisterRenderTask()
{
	/////////////////////////////////////////////////////
	///			�`��^�X�N
	/////////////////////////////////////////////////////
	m_RenderTask.AddTask("RenderScene", TASK_MAIN1,
		[&]()
	{
		if (m_Scene)
		{
			m_Scene->Render();
		}
	}
	);

}

void ActionGame::SceneManager::RegisterRender2DTask()
{
	/////////////////////////////////////////////////////
	///			2D�`��^�X�N
	/////////////////////////////////////////////////////
	m_Render2DTask.AddTask("Render2DScene", TASK_MAIN2,
		[&]()
	{
		if (m_Scene)
		{
			m_Scene->Render2D();
		}
	}
	);
	
}

void ActionGame::SceneManager::DeleteTask()
{
	m_UpdateTask.DeleteTask("UpdateScene");
	m_RenderTask.DeleteTask("RenderScene");
	m_Render2DTask.DeleteTask("Render2DScene");
}

void ActionGame::SceneManager::RegisterDebugTask()
{
	/////////////////////////////////////////////////////
	///			�f�o�b�O�^�X�N
	/////////////////////////////////////////////////////

	//�X�V
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

	//�`��
	m_RenderTask.AddTask("RenderDebug", TASK_MAIN1,
		[&]()
			{
				if (m_Scene)
				{
					m_Scene->RenderDebug();
				}
				
			}
		);
	//�QD�`��
	m_Render2DTask.AddTask("RenderDebug2D", TASK_MAIN3,
		[&]()
	{
		if (m_Scene)
		{
			m_Scene->Render2DDebug();
		}
	}
	);

}

void ActionGame::SceneManager::DeleteDebugTask()
{
	m_UpdateTask.DeleteTask("UpdateDebug");
	m_RenderTask.DeleteTask("RenderDebug");
	m_Render2DTask.DeleteTask("RenderDebug2D");
}

void ActionGame::SceneManager::RegisterSceneChangeEffectTask()
{
	/////////////////////////////////////////////////////
	///			�V�[���J�ڃG�t�F�N�g�^�X�N
	/////////////////////////////////////////////////////

	//�X�V
	m_UpdateTask.AddTask("SceneChangeEffectUpdate", TASK_MAIN1,
		[&]()
			{
				m_SceneEffect->Update();
				if (m_SceneEffect->IsHalfPoint() && !m_SceneInitFlg)
				{
					m_Scene->Initialize();
					m_SceneInitFlg = true;
				}
				if (m_SceneEffect->IsEnd())
				{
					
					DeleteSceneChangeEffectTask();
				}
			}
	);

	//�QD�`��
	m_Render2DTask.AddTask("SceneChangeEffectRender", TASK_MAIN3,
		[&]()
	{
		m_SceneEffect->Render(m_Scene, m_Scene);
	}
	);
}

void ActionGame::SceneManager::DeleteSceneChangeEffectTask()
{
	/////////////////////////////////////////////////////
	///			2D�`��^�X�N
	/////////////////////////////////////////////////////
	m_UpdateTask.DeleteTask("SceneChangeEffectUpdate");

	m_Render2DTask.DeleteTask("SceneChangeEffectRender");
}