#include "SceneManager.h"
#include "LoadingScene.h"

using namespace Scene;



Scene::SceneManager::SceneManager()
	: isDebug_(false)
	, isSceneInit_(false)
	, scene_()
{
}

Scene::SceneManager::~SceneManager()
{

}

void Scene::SceneManager::RegistScene(SCENENO sceneNo, SceneCreatorPtr creator)
{
	sceneMap_[sceneNo] = std::move(creator);
}

bool Scene::SceneManager::ChangeScene(SCENENO sceneNo)
{
	//古いシーンを破棄
	if (scene_)
	{
		scene_->Release();
	}

	//シーン作成
	ScenePtr temp = sceneMap_[sceneNo]->Create();
	temp->Load();
	temp->Initialize();

	scene_ = temp;

	return true;
}

bool Scene::SceneManager::ChangeScene(const ScenePtr& scene)
{
	auto temp = scene;
	//古いシーンを破棄
	if (scene_)
	{
		scene_->Release();
	}
	scene_ = temp;
	return true;
}

void Scene::SceneManager::InitializeScene(SceneChangeEffectPtr effect)
{
	sceneEffect_ = effect;
	isSceneInit_ = false;
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
	ScenePtr temp = sceneMap_[sceneNo]->Create();

	//古いシーンを破棄
	if (scene_)
	{
		scene_->Release();
	}

	//ローディングシーン作成
	auto loading = std::make_shared<Scene::LoadingScene>(temp);
	loading->Load();
	loading->Initialize();

	scene_ = loading;

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
		isDebug_ = !isDebug_;
		if (isDebug_)
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
	if (scene_)
	{
		scene_->Release();
	}
}


void Scene::SceneManager::RegisterTask()
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
	updateTask_.AddTask("UpdateScene", Task::PRIORITY::MAIN1,
		[&]()
			{
				if (scene_)
				{
					scene_->Update();
				}
			}
		);
	
}

void Scene::SceneManager::RegisterRenderTask()
{
	/////////////////////////////////////////////////////
	///			描画タスク
	/////////////////////////////////////////////////////
	renderTask_.AddTask("RenderScene", Task::PRIORITY::MAIN1,
		[&]()
	{
		if (scene_)
		{
			scene_->Render();
		}
	}
	);

}

void Scene::SceneManager::RegisterRender2DTask()
{
	/////////////////////////////////////////////////////
	///			2D描画タスク
	/////////////////////////////////////////////////////
	render2DTask_.AddTask("Render2DScene", Task::PRIORITY::MAIN2,
		[&]()
	{
		if (scene_)
		{
			scene_->Render2D();
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
	updateTask_.AddTask("UpdateDebug", Task::PRIORITY::MAIN1,
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
	renderTask_.AddTask("RenderDebug", Task::PRIORITY::MAIN1,
		[&]()
			{
				if (scene_)
				{
					scene_->RenderDebug();
				}
				
			}
		);
	//２D描画
	render2DTask_.AddTask("RenderDebug2D", Task::PRIORITY::MAIN3,
		[&]()
	{
		if (scene_)
		{
			scene_->Render2DDebug();
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
	updateTask_.AddTask("SceneChangeEffectUpdate", Task::PRIORITY::MAIN1,
		[&]()
			{
				sceneEffect_->Update();
				if (sceneEffect_->IsHalfPoint() && !isSceneInit_)
				{
					scene_->Initialize();
					isSceneInit_ = true;
				}
				if (sceneEffect_->IsEnd())
				{
					DeleteSceneChangeEffectTask();
				}
			}
	);

	//２D描画
	render2DTask_.AddTask("SceneChangeEffectRender", Task::PRIORITY::MAIN3,
		[&]()
	{
		sceneEffect_->Render(scene_, scene_);
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