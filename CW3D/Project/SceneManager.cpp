#include "SceneManager.h"
#include "LoadingScene.h"

using namespace Scene;



Scene::CSceneManager::CSceneManager()
	: isDebug_(false)
	, isSceneInit_(false)
	, currentScene_()
	, prevScene_()
	, changeEffect_()
{
}

Scene::CSceneManager::~CSceneManager()
{

}

void Scene::CSceneManager::RegistScene(SCENENO sceneNo, SceneCreatorPtr creator)
{
	sceneMap_[sceneNo] = std::move(creator);
}

void Scene::CSceneManager::InitializeScene(SceneChangeEffectPtr effect)
{
	changeEffect_ = effect;
	isSceneInit_ = false;
	RegisterSceneChangeEffectTask();

}

bool Scene::CSceneManager::ChangeScene(SCENENO sceneNo)
{
	//シーン作成
	auto temp = sceneMap_[sceneNo]->Create();
	temp->Load();
	temp->Initialize();
	currentScene_ = temp;

	return true;
}

bool Scene::CSceneManager::ChangeScene(SCENENO sceneNo,SceneChangeEffectPtr effect)
{
	//変更中なら失敗
	if (currentScene_ && prevScene_ && changeEffect_)
	{
		return false;
	}

	//古いシーンを破棄
	if (currentScene_)
	{
		changeEffect_ = effect;
		prevScene_ = currentScene_;
		currentScene_.reset();
	}

	return ChangeScene(sceneNo);
}

bool Scene::CSceneManager::ChangeScene(const ScenePtr& scene, SceneChangeEffectPtr effect)
{
	//変更中なら失敗
	if (currentScene_ && prevScene_ && changeEffect_)
	{
		return false;
	}

	auto temp = scene;
	//古いシーンを破棄
	if (currentScene_)
	{
		changeEffect_ = effect;
		prevScene_ = currentScene_;
		currentScene_.reset();
	}
	currentScene_ = temp;
	return true;
}



bool Scene::CSceneManager::ChangeScene(SCENENO sceneNo, SceneChangeEffectPtr effect, bool isLoading)
{
	//ロードを挟まないなら普通にシーン切り替え
	if (!isLoading)
	{
		return ChangeScene(sceneNo, effect);
	}

	//変更中なら失敗
	if (currentScene_ && prevScene_ && changeEffect_)
	{
		return false;
	}

	//古いシーンを破棄
	if (currentScene_)
	{
		changeEffect_ = effect;
		prevScene_ = currentScene_;
		currentScene_.reset();
	}

	//次のシーン作成
	auto nextScene = sceneMap_[sceneNo]->Create();
	//ローディングシーン作成
	auto loadingScene = std::make_shared<Scene::CLoadingScene>(nextScene);
	loadingScene->Load();
	loadingScene->Initialize();

	currentScene_ = loadingScene;

	return true;
}


bool Scene::CSceneManager::Load()
{

	return true;
}

void Scene::CSceneManager::Initialize()
{
	updateTask_.DeleteAllTaskImmediate();
	renderTask_.DeleteAllTaskImmediate();
	render2DTask_.DeleteAllTaskImmediate();
	//タスク登録
	RegisterTask();
}

void Scene::CSceneManager::Update()
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

void Scene::CSceneManager::Render()
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

void Scene::CSceneManager::Release()
{
	if (prevScene_)
	{
		prevScene_->Release();
		prevScene_.reset();
	}
	if (currentScene_)
	{
		currentScene_->Release();
		currentScene_.reset();
	}
}


void Scene::CSceneManager::RegisterTask()
{
	//更新タスク
	RegisterUpdateTask();
	//描画タスク
	RegisterRenderTask();
	//2D描画タスク
	RegisterRender2DTask();
}

void Scene::CSceneManager::RegisterUpdateTask()
{
	/////////////////////////////////////////////////////
	///			更新タスク
	/////////////////////////////////////////////////////
	updateTask_.AddTask("UpdateScene", Task::PRIORITY::MAIN1,
		[&]()
		{
				if (currentScene_ && prevScene_ && changeEffect_)
				{
					currentScene_->Update();
					changeEffect_->Update();
					if (changeEffect_->IsEnd())
					{
						prevScene_->Release();
						prevScene_.reset();
						changeEffect_.reset();
					}
				}
				else if (currentScene_)
				{ 
					currentScene_->Update(); 
				}
		}
		);
	
}

void Scene::CSceneManager::RegisterRenderTask()
{
	/////////////////////////////////////////////////////
	///			描画タスク
	/////////////////////////////////////////////////////
	renderTask_.AddTask("RenderScene", Task::PRIORITY::MAIN1,
		[&]()
		{
				if(currentScene_ && (prevScene_ == nullptr || changeEffect_ == nullptr))
				{
					currentScene_->Render();
				}
		}
		);

}

void Scene::CSceneManager::RegisterRender2DTask()
{
	/////////////////////////////////////////////////////
	///			2D描画タスク
	/////////////////////////////////////////////////////
	render2DTask_.AddTask("Render2DScene", Task::PRIORITY::MAIN2,
		[&]()
	{
		if (currentScene_ && prevScene_ && changeEffect_)
		{
			changeEffect_->Render(prevScene_, currentScene_);

		}
		else if (currentScene_)
		{
			currentScene_->Render2D();
		}
	}
	);
	
}

void Scene::CSceneManager::DeleteTask()
{
	updateTask_.DeleteTask("UpdateScene");
	renderTask_.DeleteTask("RenderScene");
	render2DTask_.DeleteTask("Render2DScene");
}

void Scene::CSceneManager::RegisterDebugTask()
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
				if (currentScene_)
				{
					currentScene_->RenderDebug();
				}
				
			}
		);
	//２D描画
	render2DTask_.AddTask("RenderDebug2D", Task::PRIORITY::MAIN3,
		[&]()
	{
		if (currentScene_)
		{
			currentScene_->Render2DDebug();
		}
	}
	);

}

void Scene::CSceneManager::DeleteDebugTask()
{
	updateTask_.DeleteTask("UpdateDebug");
	renderTask_.DeleteTask("RenderDebug");
	render2DTask_.DeleteTask("RenderDebug2D");
}

void Scene::CSceneManager::RegisterSceneChangeEffectTask()
{
	/////////////////////////////////////////////////////
	///			シーン遷移エフェクトタスク
	/////////////////////////////////////////////////////

	//更新
	updateTask_.AddTask("SceneChangeEffectUpdate", Task::PRIORITY::MAIN1,
		[&]()
			{
				changeEffect_->Update();
				if (changeEffect_->IsHalfPoint() && !isSceneInit_)
				{
					currentScene_->Initialize();
					isSceneInit_ = true;
				}
				if (changeEffect_->IsEnd())
				{
					DeleteSceneChangeEffectTask();
				}
			}
	);

	//２D描画
	render2DTask_.AddTask("SceneChangeEffectRender", Task::PRIORITY::MAIN3,
		[&]()
	{
		changeEffect_->Render(currentScene_, currentScene_);
	}
	);
}

void Scene::CSceneManager::DeleteSceneChangeEffectTask()
{
	/////////////////////////////////////////////////////
	///			2D描画タスク
	/////////////////////////////////////////////////////
	updateTask_.DeleteTask("SceneChangeEffectUpdate");

	render2DTask_.DeleteTask("SceneChangeEffectRender");
}