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
	//�V�[���쐬
	auto temp = sceneMap_[sceneNo]->Create();
	temp->Load();
	temp->Initialize();
	currentScene_ = temp;

	return true;
}

bool Scene::CSceneManager::ChangeScene(SCENENO sceneNo,SceneChangeEffectPtr effect)
{
	//�ύX���Ȃ玸�s
	if (currentScene_ && prevScene_ && changeEffect_)
	{
		return false;
	}

	//�Â��V�[����j��
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
	//�ύX���Ȃ玸�s
	if (currentScene_ && prevScene_ && changeEffect_)
	{
		return false;
	}

	auto temp = scene;
	//�Â��V�[����j��
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
	//���[�h�����܂Ȃ��Ȃ畁�ʂɃV�[���؂�ւ�
	if (!isLoading)
	{
		return ChangeScene(sceneNo, effect);
	}

	//�ύX���Ȃ玸�s
	if (currentScene_ && prevScene_ && changeEffect_)
	{
		return false;
	}

	//�Â��V�[����j��
	if (currentScene_)
	{
		changeEffect_ = effect;
		prevScene_ = currentScene_;
		currentScene_.reset();
	}

	//���̃V�[���쐬
	auto nextScene = sceneMap_[sceneNo]->Create();
	//���[�f�B���O�V�[���쐬
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
	//�^�X�N�o�^
	RegisterTask();
}

void Scene::CSceneManager::Update()
{
	//�f�o�b�O�؂�ւ�
	if (g_pInput->IsKeyHold(MOFKEY_LCONTROL) && g_pInput->IsKeyPush(MOFKEY_F1))
	{
		isDebug_ = !isDebug_;
		if (isDebug_)
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

void Scene::CSceneManager::Render()
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
	//�X�V�^�X�N
	RegisterUpdateTask();
	//�`��^�X�N
	RegisterRenderTask();
	//2D�`��^�X�N
	RegisterRender2DTask();
}

void Scene::CSceneManager::RegisterUpdateTask()
{
	/////////////////////////////////////////////////////
	///			�X�V�^�X�N
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
	///			�`��^�X�N
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
	///			2D�`��^�X�N
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
	///			�f�o�b�O�^�X�N
	/////////////////////////////////////////////////////

	//�X�V
	updateTask_.AddTask("UpdateDebug", Task::PRIORITY::MAIN1,
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
	renderTask_.AddTask("RenderDebug", Task::PRIORITY::MAIN1,
		[&]()
			{
				if (currentScene_)
				{
					currentScene_->RenderDebug();
				}
				
			}
		);
	//�QD�`��
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
	///			�V�[���J�ڃG�t�F�N�g�^�X�N
	/////////////////////////////////////////////////////

	//�X�V
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

	//�QD�`��
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
	///			2D�`��^�X�N
	/////////////////////////////////////////////////////
	updateTask_.DeleteTask("SceneChangeEffectUpdate");

	render2DTask_.DeleteTask("SceneChangeEffectRender");
}