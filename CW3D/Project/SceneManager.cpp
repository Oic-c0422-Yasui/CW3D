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
	//古いシーンを破棄
	if (m_Scene)
	{
		m_Scene->Release();
	}

	//シーン作成
	ScenePtr temp = m_SceneMap[sceneNo]->Create();
	temp->Load();
	temp->Initialize();

	m_Scene = temp;

	return true;
}

bool ActionGame::SceneManager::ChangeScene(const ScenePtr& scene)
{
	auto temp = scene;
	//古いシーンを破棄
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
	//ロードを挟まないなら普通にシーン切り替え
	if (!isLoading)
	{
		return ChangeScene(sceneNo);
	}

	//シーン作成
	ScenePtr temp = m_SceneMap[sceneNo]->Create();

	//古いシーンを破棄
	if (m_Scene)
	{
		m_Scene->Release();
	}

	//ローディングシーン作成
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
	//タスク登録
	RegisterTask();
}

void SceneManager::Update()
{
	//デバッグ切り替え
	if (g_pInput->IsKeyPush(MOFKEY_F1))
	{
		m_DebugFlg = m_DebugFlg ? false : true;
		if (m_DebugFlg)
		{
			//デバッグタスク登録
			RegisterDebugTask();
		}
		else
		{
			//デバッグタスク削除
			DeleteDebugTask();
		}
	}

	//更新タスク
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
	//更新タスク
	RegisterUpdateTask();
}

void ActionGame::SceneManager::RegisterUpdateTask()
{
	/////////////////////////////////////////////////////
	///			更新タスク
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
	///			デバッグタスク
	/////////////////////////////////////////////////////
	m_UpdateTask.AddTask("UpdateDebug", TASK_MAIN1,
		[&]()
			{
				//シーン遷移
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
