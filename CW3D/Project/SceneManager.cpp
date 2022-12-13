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
	m_SceneEffect = effect;
	m_SceneInitFlg = false;
	RegisterSceneChangeEffectTask();
	
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
	m_RenderTask.DeleteAllTaskImmediate();
	m_Render2DTask.DeleteAllTaskImmediate();
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
	
	//深度バッファ有効化
	g_pGraphics->SetDepthEnable(TRUE);
	if (m_DebugFlg)
	{
		int a;
		a = 1;
	}
	//描画タスク
	m_RenderTask.Excution();

	//深度バッファ無効化
	g_pGraphics->SetDepthEnable(FALSE);

	//描画タスク
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
	//更新タスク
	RegisterUpdateTask();
	//描画タスク
	RegisterRenderTask();
	//2D描画タスク
	RegisterRender2DTask();
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

void ActionGame::SceneManager::RegisterRenderTask()
{
	/////////////////////////////////////////////////////
	///			描画タスク
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
	///			2D描画タスク
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
	///			デバッグタスク
	/////////////////////////////////////////////////////

	//更新
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

	//描画
	m_RenderTask.AddTask("RenderDebug", TASK_MAIN1,
		[&]()
			{
				if (m_Scene)
				{
					m_Scene->RenderDebug();
				}
				
			}
		);
	//２D描画
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
	///			シーン遷移エフェクトタスク
	/////////////////////////////////////////////////////

	//更新
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

	//２D描画
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
	///			2D描画タスク
	/////////////////////////////////////////////////////
	m_UpdateTask.DeleteTask("SceneChangeEffectUpdate");

	m_Render2DTask.DeleteTask("SceneChangeEffectRender");
}