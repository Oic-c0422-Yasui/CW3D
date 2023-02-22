#include "SceneManager.h"
#include "LoadingScene.h"

using namespace Scene;



Scene::SceneManager::SceneManager()
	: m_DebugFlg(false)
	, m_SceneInitFlg(false)
	, m_Scene()
{
}

Scene::SceneSceneManager::~SceneManager()
{

}

void Scene::SceneManager::RegistScene(SCENENO sceneNo, SceneCreatorPtr creator)
{
	m_SceneMap[sceneNo] = std::move(creator);
}

bool Scene::SceneManager::ChangeScene(SCENENO sceneNo)
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

bool Scene::SceneManager::ChangeScene(const ScenePtr& scene)
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

void Scene::SceneManager::InitializeScene(SceneChangeEffectPtr effect)
{
	m_SceneEffect = effect;
	m_SceneInitFlg = false;
	RegisterSceneChangeEffectTask();
	
}

bool Scene::SceneManager::ChangeScene(SCENENO sceneNo, bool isLoading)
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


bool Scene::SceneManager::Load()
{

	return true;
}

void Scene::SceneManager::Initialize()
{
	updateTask_.DeleteAllTaskImmediate();
	renderTask_.DeleteAllTaskImmediate();
	render2DTask_.DeleteAllTaskImmediate();
	//�^�X�N�o�^
	RegisterTask();
}

void Scene::SceneManager::Update()
{
	//�f�o�b�O�؂�ւ�
	if (g_pInput->IsKeyHold(MOFKEY_LCONTROL) && g_pInput->IsKeyPush(MOFKEY_F1))
	{
		m_DebugFlg = !m_DebugFlg;
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
	updateTask_.Excution();

}

void Scene::SceneManager::Render()
{
	
	//�[�x�o�b�t�@�L����
	g_pGraphics->SetDepthEnable(TRUE);

	//�`��^�X�N
	renderTask_.Excution();

	//�[�x�o�b�t�@������
	g_pGraphics->SetDepthEnable(FALSE);

	//�`��^�X�N
	render2DTask_.Excution();
}

void Scene::SceneManager::Release()
{
	if (m_Scene)
	{
		m_Scene->Release();
		m_Scene.reset();
	}
}


voidScene::SceneManager::RegisterTask()
{
	//�X�V�^�X�N
	RegisterUpdateTask();
	//�`��^�X�N
	RegisterRenderTask();
	//2D�`��^�X�N
	RegisterRender2DTask();
}

void Scene::SceneManager::RegisterUpdateTask()
{
	/////////////////////////////////////////////////////
	///			�X�V�^�X�N
	/////////////////////////////////////////////////////
	updateTask_.AddTask("UpdateScene", TASK_MAIN1,
		[&]()
			{
				if (m_Scene)
				{
					m_Scene->Update();
				}
			}
		);
	
}

void Scene::SceneManager::RegisterRenderTask()
{
	/////////////////////////////////////////////////////
	///			�`��^�X�N
	/////////////////////////////////////////////////////
	renderTask_.AddTask("RenderScene", TASK_MAIN1,
		[&]()
	{
		if (m_Scene)
		{
			m_Scene->Render();
		}
	}
	);

}

void Scene::SceneManager::RegisterRender2DTask()
{
	/////////////////////////////////////////////////////
	///			2D�`��^�X�N
	/////////////////////////////////////////////////////
	render2DTask_.AddTask("Render2DScene", TASK_MAIN2,
		[&]()
	{
		if (m_Scene)
		{
			m_Scene->Render2D();
		}
	}
	);
	
}

void Scene::SceneManager::DeleteTask()
{
	updateTask_.DeleteTask("UpdateScene");
	renderTask_.DeleteTask("RenderScene");
	render2DTask_.DeleteTask("Render2DScene");
}

void Scene::SceneManager::RegisterDebugTask()
{
	/////////////////////////////////////////////////////
	///			�f�o�b�O�^�X�N
	/////////////////////////////////////////////////////

	//�X�V
	updateTask_.AddTask("UpdateDebug", TASK_MAIN1,
		[&]()
			{
				//�V�[���J��
				if (g_pInput->IsKeyHold(MOFKEY_LCONTROL))
				{
					if (g_pInput->IsKeyPush(MOFKEY_1))
					{
						ChangeScene(SCENENO::TITLE);
					}
					else if (g_pInput->IsKeyPush(MOFKEY_2))
					{
						ChangeScene(SCENENO::GAME);
					}
				}
			}
		);

	//�`��
	renderTask_.AddTask("RenderDebug", TASK_MAIN1,
		[&]()
			{
				if (m_Scene)
				{
					m_Scene->RenderDebug();
				}
				
			}
		);
	//�QD�`��
	render2DTask_.AddTask("RenderDebug2D", TASK_MAIN3,
		[&]()
	{
		if (m_Scene)
		{
			m_Scene->Render2DDebug();
		}
	}
	);

}

void Scene::SceneManager::DeleteDebugTask()
{
	updateTask_.DeleteTask("UpdateDebug");
	renderTask_.DeleteTask("RenderDebug");
	render2DTask_.DeleteTask("RenderDebug2D");
}

void Scene::SceneManager::RegisterSceneChangeEffectTask()
{
	/////////////////////////////////////////////////////
	///			�V�[���J�ڃG�t�F�N�g�^�X�N
	/////////////////////////////////////////////////////

	//�X�V
	updateTask_.AddTask("SceneChangeEffectUpdate", TASK_MAIN1,
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
	render2DTask_.AddTask("SceneChangeEffectRender", TASK_MAIN3,
		[&]()
	{
		m_SceneEffect->Render(m_Scene, m_Scene);
	}
	);
}

void Scene::SceneManager::DeleteSceneChangeEffectTask()
{
	/////////////////////////////////////////////////////
	///			2D�`��^�X�N
	/////////////////////////////////////////////////////
	updateTask_.DeleteTask("SceneChangeEffectUpdate");

	render2DTask_.DeleteTask("SceneChangeEffectRender");
}