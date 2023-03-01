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
	//�Â��V�[����j��
	if (scene_)
	{
		scene_->Release();
	}

	//�V�[���쐬
	ScenePtr temp = sceneMap_[sceneNo]->Create();
	temp->Load();
	temp->Initialize();

	scene_ = temp;

	return true;
}

bool Scene::SceneManager::ChangeScene(const ScenePtr& scene)
{
	auto temp = scene;
	//�Â��V�[����j��
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
	//���[�h�����܂Ȃ��Ȃ畁�ʂɃV�[���؂�ւ�
	if (!isLoading)
	{
		return ChangeScene(sceneNo);
	}

	//�V�[���쐬
	ScenePtr temp = sceneMap_[sceneNo]->Create();

	//�Â��V�[����j��
	if (scene_)
	{
		scene_->Release();
	}

	//���[�f�B���O�V�[���쐬
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
	//�^�X�N�o�^
	RegisterTask();
}

void Scene::SceneManager::Update()
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
	if (scene_)
	{
		scene_->Release();
	}
}


void Scene::SceneManager::RegisterTask()
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
	///			�`��^�X�N
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
	///			2D�`��^�X�N
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
				if (scene_)
				{
					scene_->RenderDebug();
				}
				
			}
		);
	//�QD�`��
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
	///			�V�[���J�ڃG�t�F�N�g�^�X�N
	/////////////////////////////////////////////////////

	//�X�V
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

	//�QD�`��
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
	///			2D�`��^�X�N
	/////////////////////////////////////////////////////
	updateTask_.DeleteTask("SceneChangeEffectUpdate");

	render2DTask_.DeleteTask("SceneChangeEffectRender");
}