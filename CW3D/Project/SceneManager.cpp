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

bool Scene::SceneManager::ChangeScene(const ScenePtr& scene)
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

void Scene::SceneManager::InitializeScene(SceneChangeEffectPtr effect)
{
	m_SceneEffect = effect;
	m_SceneInitFlg = false;
	RegisterSceneChangeEffectTask();
	
}

bool Scene::SceneManager::ChangeScene(SCENENO sceneNo, bool isLoading)
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


bool Scene::SceneManager::Load()
{

	return true;
}

void Scene::SceneManager::Initialize()
{
	updateTask_.DeleteAllTaskImmediate();
	renderTask_.DeleteAllTaskImmediate();
	render2DTask_.DeleteAllTaskImmediate();
	//タスク登録
	RegisterTask();
}

void Scene::SceneManager::Update()
{
	//デバッグ切り替え
	if (g_pInput->IsKeyHold(MOFKEY_LCONTROL) && g_pInput->IsKeyPush(MOFKEY_F1))
	{
		m_DebugFlg = !m_DebugFlg;
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
	updateTask_.Excution();

}

void Scene::SceneManager::Render()
{
	
	//深度バッファ有効化
	g_pGraphics->SetDepthEnable(TRUE);

	//描画タスク
	renderTask_.Excution();

	//深度バッファ無効化
	g_pGraphics->SetDepthEnable(FALSE);

	//描画タスク
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
	//更新タスク
	RegisterUpdateTask();
	//描画タスク
	RegisterRenderTask();
	//2D描画タスク
	RegisterRender2DTask();
}

void Scene::SceneManager::RegisterUpdateTask()
{
	/////////////////////////////////////////////////////
	///			更新タスク
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
	///			描画タスク
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
	///			2D描画タスク
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
	///			デバッグタスク
	/////////////////////////////////////////////////////

	//更新
	updateTask_.AddTask("UpdateDebug", TASK_MAIN1,
		[&]()
			{
				//シーン遷移
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

	//描画
	renderTask_.AddTask("RenderDebug", TASK_MAIN1,
		[&]()
			{
				if (m_Scene)
				{
					m_Scene->RenderDebug();
				}
				
			}
		);
	//２D描画
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
	///			シーン遷移エフェクトタスク
	/////////////////////////////////////////////////////

	//更新
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

	//２D描画
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
	///			2D描画タスク
	/////////////////////////////////////////////////////
	updateTask_.DeleteTask("SceneChangeEffectUpdate");

	render2DTask_.DeleteTask("SceneChangeEffectRender");
}