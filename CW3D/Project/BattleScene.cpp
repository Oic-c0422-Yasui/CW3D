#include "BattleScene.h"
#include "HPPresenter.h"
#include	"SkillPresenter.h"

#include	"CollisionEnemyEnemy.h"
#include	"CollisionPlayerEnemy.h"
#include	"CollisionShotEnemy.h"
#include	"CollisionShotPlayer.h"
#include	"CollisionObjectPlayer.h"
#include	"CollisionObjectEnemy.h"
#include	"NomalCamera.h"

#include	"ActorObjectManager.h"
#include	"Stage1.h"
#include	"JsonStageLoader.h"	


using namespace ActionGame;



Scene::CBattleScene::CBattleScene()
	: player_(std::make_shared<CPlayer>())
	, enemyManager_()
	, enemySpawner_(std::make_shared<Spawner::EnemySpawnerArray>())
	, currentGameState_(GAME_STATE::NOMAL)
{
}

Scene::CBattleScene::~CBattleScene()
{
}

bool Scene::CBattleScene::Load()
{
	


	//���b�V���ǂݍ���
	std::shared_ptr<CMeshContainer> tempMesh = std::make_shared<CMeshContainer>();
	if (tempMesh->Load("chara.mom") != MOFMODEL_RESULT_SUCCEEDED)
	{
		return false;
	}
	ResourcePtrManager<CMeshContainer>::GetInstance().AddResource("Player", "Player", tempMesh);

	
	//�e�N�X�`���ǂݍ���
	if (!uiCreater_.Create())
	{
		return false;
	}

	//�G�t�F�N�g�ǂݍ���
	EffectRendererInstance.Initialize();
	Effekseer::EffectRef effect = Effekseer::Effect::Create(EffectRendererInstance.GetManager(), u"Effect/Laser01.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResource("Effect", "AttackEffect1", effect);
	effect = Effekseer::Effect::Create(EffectRendererInstance.GetManager(), u"Effect/sword.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResource("Effect", "DamageEffect1", effect);
	effect = Effekseer::Effect::Create(EffectRendererInstance.GetManager(), u"Effect/tuki.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResource("Effect", "AttackEffect2", effect);
	effect = Effekseer::Effect::Create(EffectRendererInstance.GetManager(), u"Effect/sandStome.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResource("Effect", "SkillEffect1", effect);
	effect = Effekseer::Effect::Create(EffectRendererInstance.GetManager(), u"Effect/Laser01.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResource("Effect", "SkillEffect2", effect);
	effect = Effekseer::Effect::Create(EffectRendererInstance.GetManager(), u"Effect/tornade.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResource("Effect", "SkillEffect3", effect);
	effect = Effekseer::Effect::Create(EffectRendererInstance.GetManager(), u"Effect/fire.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResource("Effect", "SkillEffect4", effect);
	effect = Effekseer::Effect::Create(EffectRendererInstance.GetManager(), u"Effect/drill.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResource("Effect", "SkillEffect5", effect);
	effect = Effekseer::Effect::Create(EffectRendererInstance.GetManager(), u"Effect/Track.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResource("Effect", "ClosedEffect", effect);
	effect = Effekseer::Effect::Create(EffectRendererInstance.GetManager(), u"Effect/Clow1.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResource("Effect", "AttackEffect3", effect);
	effect = Effekseer::Effect::Create(EffectRendererInstance.GetManager(), u"Effect/A_Sylph2.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResource("Effect", "EscapeEffect", effect);

	//�X�e�[�W���ǂݍ���
	JsonStageLoader stageLoader;
	stageLoader.Load("Text/Stage1.json");
	//�X�e�[�W�ǂݍ���
	StagePtr stage = std::make_shared<CStage1>();
	stageManager_.Load(stage, stageLoader.GetDivisionArray());


	//�v���C���[�ǂݍ���
	auto input = InputManagerInstance.GetInput(0);
	player_->SetInput(input);
	if (!player_->Load())
	{
		return false;
	}
	//�T�[�r�X���P�[�^�[�̐ݒ�
	ServiceLocator<CPlayer>::SetService(player_);

	//�v���C���[UI�ǂݍ���
	playerUiRender_ = std::make_shared<CPlayerUIRender>();
	playerUiRender_->Load();
	CHPPresenter::Present(player_, playerUiRender_->GetHPRender());


	//�J�����ǂݍ���
	CameraPtr camera = std::make_shared<NomalCamera>(player_->GetPosition(), player_->GetPosition(),Vector3(0,0,0), Vector3(0, 0, 0));
	CameraControllerInstance.Load(camera);

	//�v���C���[���}�l�[�W���[�ɓo�^
	ActorObjectManagerInstance.Add(player_);
	
	//�t�H���g�쐬
	font_.Create(225, "�l�r �S�V�b�N");

	return true;
}

void Scene::CBattleScene::Initialize()
{
	//�C���X�^���X���Z�b�g
	EffectControllerInstance.Reset();
	ShotManagerInstance.Reset();
	CameraControllerInstance.SetDefault();
	TimeScaleControllerInstance.Reset();
	
	//�^�X�N���Z�b�g
	updateTask_.DeleteAllTaskImmediate();
	renderTask_.DeleteAllTaskImmediate();
	render2DTask_.DeleteAllTaskImmediate();

	//�^�C�}�[�J�n
	timer_.Start();

	//�X�e�[�W�}�l�[�W���[������
	stageManager_.Initialize();

	//�v���C���[������
	player_->Initialize();
	playerUiRender_->Initialize();

	//�N���A�����̃v���o�C�_�[�ɃI�u�U�[�o�[��o�^
	clearTermProvider_ = std::make_shared<ClearTermProvider>();
	auto& provider = clearTermProvider_;
	enemyManager_.GetEnemyCountSubject().Subscribe([provider](size_t count) {provider->SetEnemyCount(count); });
	enemyManager_.GetBossCountSubject().Subscribe([provider](size_t count) {provider->SetBossCount(count); });
	timer_.GetTimeSubject().Subscribe([provider](float time) { provider->SetDivisionTime(time); });
	
	//�G����
	enemyCreateThread_.Create( [this]() { return CreateEnemys(); },
								[this]() {RegisterAfterSpawn(); }
								);
	
	//���C�g�ݒ�
	light_.SetDirection(Vector3(0.0f, -1.0f, 1.0f));
	CGraphicsUtilities::SetDirectionalLight(&light_);
	light_.SetAmbient(MOF_XRGB(255, 255, 255));
	light_.SetDiffuse(MOF_XRGB(220, 220, 220));
	light_.SetSpeculer(MOF_XRGB(255, 255, 255));

	//�Q�[���̏�ԏ�����
	currentGameState_ = GAME_STATE::NOMAL;


	//�^�X�N�̓o�^
	RegisterTask();

}
void Scene::CBattleScene::Update()
{

	if (currentGameState_ == GAME_STATE::CLEAR || 
		currentGameState_ == GAME_STATE::OVER)
	{
		//�J��
		if (InputManagerInstance.GetInput(0)->IsPush(INPUT_KEY_BACK))
		{
			//�^�C�g���֑J��
			SceneChangeService::GetService()->ChangeScene(SCENENO::TITLE);
			return;
		}
	}

	//�X�V�^�X�N���s
	updateTask_.Excution();


	//�G�t�F�N�g�`��X�V
	EffectRendererInstance.Update();
	//�G�t�F�N�g����X�V
	EffectControllerInstance.Update();
	//���ԑ���X�V
	TimeScaleControllerInstance.Update();
	//�J��������X�V
	CameraControllerInstance.Update(player_->GetPosition(), player_->GetPosition());
	//�V���b�g�}�l�[�W���[�X�V
	ShotManagerInstance.Update();

	//�V���b�g�폜����
	ShotManagerInstance.Delete();
	//�G�t�F�N�g�폜����
	EffectControllerInstance.Delete();
	//�A�N�^�[�폜����
	ActorObjectManagerInstance.Delete();
	
}

void Scene::CBattleScene::Render()
{
	//�`��^�X�N���s
	renderTask_.Excution();

}

void Scene::CBattleScene::RenderDebug()
{
	//�X�e�[�W�f�o�b�O�`��
	stageManager_.RenderDebug();

	//�V���b�g�f�o�b�O�`��
	for (size_t i = 0; i < ShotManagerInstance.GetShotCount(); i++)
	{
		auto& shot = ShotManagerInstance.GetShot(i);

		if (!shot->IsShow() || !shot->IsEnableCollider())
		{
			continue;
		}
		switch (shot->GetCollisionType())
		{
		case COLLISION_TYPE::SPHERE:
		{
			CGraphicsUtilities::RenderLineSphere(shot->GetColliderSphere(), Vector4(1, 0, 0, 0.2f));
			break;
		}
		case COLLISION_TYPE::AABB:
		{
			CGraphicsUtilities::RenderBox(shot->GetColliderAABB(), Vector4(1, 0, 0, 0.2f)); 
			break;
		}
		case COLLISION_TYPE::OBB:
		{
			CGraphicsUtilities::RenderBox(shot->GetColliderOBB(), Vector4(1, 0, 0, 0.2f));
			break;
		}
		default:
			break;
		}
	}
	//�v���C���[�����蔻��f�o�b�O�`��
	CGraphicsUtilities::RenderBox(player_->GetCollider(), Vector4(0, 1, 0, 0.2f));
	//�v���C���[����������蔻��f�o�b�O�`��
	if (player_->IsEscape())
	{
		CGraphicsUtilities::RenderBox(player_->GetEscapeCollider(), Vector4(0, 0, 1, 0.2f));
	}
	if (enemyCreateThread_.IsComplete())
	{
		//�G�����蔻��f�o�b�O�`��
		enemyManager_.RenderDebug();
	}
}

void Scene::CBattleScene::Render2D()
{
	//�QD�`��^�X�N���s
	render2DTask_.Excution();

}

void Scene::CBattleScene::Render2DDebug()
{
	CGraphicsUtilities::RenderString(0, 0, "POS X:%.2f,Z:%.2f", player_->GetPosition().x, player_->GetPosition().z);
	CGraphicsUtilities::RenderString(0, 30, "VEL X:%.2f,Z:%.2f", player_->GetVelocity().x, player_->GetVelocity().z);

	CGraphicsUtilities::RenderString(0, 60, "�p�x�F%.2f", MOF_ToDegree(player_->GetRotate().y));
	CGraphicsUtilities::RenderString(0, 90, player_->IsReverse() ? "�����F��" :"�����F�E");

	CGraphicsUtilities::RenderString(400, 0, "�^�C���X�P�[���F%.2f", TimeScaleControllerInstance.GetTimeScale());
	Vector2 pos;
	g_pInput->GetMousePos(pos);
	CGraphicsUtilities::RenderString(400, 30, "X:%.1f Y:%.1f", pos.x, pos.y);
	if (enemyCreateThread_.IsComplete())
	{
		CGraphicsUtilities::RenderString(10, 180, enemyManager_.GetEnemy(0)->GetName().c_str());
	}

}

void Scene::CBattleScene::Release()
{
	//�A�N�^�[�}�l�[�W���[���
	ActorObjectManagerInstance.Release();
	//�A�N�^�[ID���
	IDManagerInstance.Release();

	//�X�e�[�W���
	stageManager_.Release();

	//�v���C���[���
	player_->Release();
	player_.reset();
	ServiceLocator<CPlayer>::Release();
	playerUiRender_.reset();

	//�G���
	enemyManager_.Release();
	enemySpawner_.reset();

	//HP�o�[���
	npcHpRender_.Release();
	
	//���\�[�X���
	ResourceManager<Effekseer::EffectRef>::GetInstance().Release();
	ResourcePtrManager<CMeshContainer>::GetInstance().Release();
	ResourcePtrManager<CSprite3D>::GetInstance().Release();
	ResourcePtrManager<CTexture>::GetInstance().Release();
	ResourcePtrManager<CFont>::GetInstance().Release();


	//�V���b�g���
	ShotManagerInstance.Reset();
	ShotManagerInstance.Release();

	//�G�t�F�N�g���
	EffectRendererInstance.Release();
	EffectControllerInstance.Release();

	//�^�C���X�P�[�����
	TimeScaleControllerInstance.Release();

	//�J�������
	CameraControllerInstance.Release();
}

bool Scene::CBattleScene::CreateEnemys()
{
	//�z�񏉊���
	enemyManager_.ClearEnemyArray();
	npcHpRender_.Reset();
	for (auto spawner : *enemySpawner_)
	{
		spawner->Reset();
	}

	//���݂̋�悩��G�̏����󂯎��
	auto division = stageManager_.GetCurrentDivision();
	auto enemysParam = division->GetEnemysParam();
	int enemyCount = division->GetEnemyCount();

	//�N���A�����ɓG�̐���ݒ�
	clearTermProvider_->SetEnemyMaxCount(enemyCount);

	//�{�X���擾
	size_t bossCount = 0;
	for (auto param : *enemysParam)
	{
		if (param->GetParam().m_IsBoss)
		{
			bossCount++;
		}
	}

	//�N���A�����Ƀ{�X�̐���ݒ�
	clearTermProvider_->SetBossMaxCount(enemyCount);

	//�G�̃X�|�i�[�擾
	auto spawner = division->GetEnemySpawners();
	enemySpawner_ = spawner;
	


	//�G�̃r���_�[�̎���
	EnemyBuilderDictionary dictionary;

	for (int i = 0; i < enemyCount; i++)
	{
		//�G�̃^�C�v�ɍ������r���_�[���擾
		auto builder = dictionary.Get(enemysParam->at(i)->GetParam().type_);

		//�G��ǉ�����
		enemyManager_.AddEnemy(builder->Create(enemysParam->at(i)));

		//�G���}�l�[�W���[�ɓo�^
		ActorObjectManagerInstance.Add(enemyManager_.GetEnemy(i));
		//�G��HP�o�[�������I�u�U�[�o�ɓo�^
		if (enemysParam->at(i)->GetParam().m_IsBoss)
		{
			auto bossHP = std::make_shared<BossHPRender>();
			CHPPresenter::Present(enemyManager_.GetEnemy(i), bossHP);
			npcHpRender_.Add(bossHP);
		}
		else
		{
			auto normalHP = std::make_shared<NormalEnemyHPRender>();
			CHPPresenter::Present(enemyManager_.GetEnemy(i), normalHP);
			npcHpRender_.Add(normalHP);
		}
		
	}

	npcHpRender_.Load();
	npcHpRender_.Initialize();

	return true;
}

void Scene::CBattleScene::RegisterTask()
{

	//�X�V�^�X�N�o�^
	RegisterUpdateTask();

	//�Փ˃^�X�N�o�^
	RegisterCollisionTask();

	//�`��^�X�N�o�^
	RegisterRenderTask();

	//�QD�`��^�X�N�o�^
	RegisterRender2DTask();

}

void Scene::CBattleScene::RegisterUpdateTask()
{
	////////////////////////////////////////////////
	///		�X�V�^�X�N
	////////////////////////////////////////////////

	//���g���C�^�X�N
	updateTask_.AddTask("RetryTask", TASK_EVENT,
		[&]()
	{
		//���g���C
		if (InputManagerInstance.GetInput(0)->IsPush(INPUT_KEY_RETRY))
		{
			//�t�F�[�h
			auto sceneEffect = std::make_shared<Scene::SceneChangeFade>(0.5f,0.5f,0.5f);
			//������
			SceneInitializeService::GetService()->InitializeScene(sceneEffect);
			return;
		}
		
	}
	);
	//�X�V�^�X�N
	updateTask_.AddTask("UpdateTask1", TASK_MAIN1,
		[&]()
	{
		
		//�^�C�}�[�X�V
		timer_.Update();

		//�v���C���[�X�V
		player_->Update();
	}
	);

	//�����̐ݒ�^�X�N
	updateTask_.AddTask("SetConditionTask", TASK_MAIN2,
		[&]()
	{

		//���S����
		if (!player_->IsShow() && player_->IsDead())
		{
			currentGameState_ = GAME_STATE::OVER;
		}

	}
	);

	
}

void Scene::CBattleScene::RegisterCollisionTask()
{

	////////////////////////////////////////////////
	///		�����蔻��^�X�N
	////////////////////////////////////////////////

	updateTask_.AddTask("CollisionTask1", TASK_COLLISION,
		[&]()
	{
		if (currentGameState_ == GAME_STATE::NOMAL)
		{
			//�v���C���[�ƃI�u�W�F�N�g�̓����蔻��
			for (size_t i = 0; i < stageManager_.GetCurrentDivision()->GetObjCount(); i++)
			{
				auto obj = stageManager_.GetCurrentDivision()->GetObj(i);
				CCollision::CollisionObj(player_, obj);
			}

			//�v���C���[�ƒe�̓����蔻��
			for (size_t i = 0; i < ShotManagerInstance.GetShotCount(); i++)
			{
				auto shot = ShotManagerInstance.GetShot(i);
				CCollision::CollisionObj(shot, player_);
			}
		}
	}
	);

}

void Scene::CBattleScene::RegisterRenderTask()
{
	////////////////////////////////////////////////
	///		�`��^�X�N
	////////////////////////////////////////////////

	renderTask_.AddTask("RenderTask1", TASK_MAIN1,
		[&]()
	{
		//�X�e�[�W�`��
		stageManager_.Render();

		//�v���C���[�`��
		player_->Render();

	}
	);
	renderTask_.AddTask("RenderTask2", TASK_MAIN3,
		[&]()
		{
			//�V���b�g�`��
			ShotManagerInstance.Render();
			//�G�t�F�N�g�`��
			EffectRendererInstance.Render();
		}
		);
}

void Scene::CBattleScene::RegisterRender2DTask()
{
	////////////////////////////////////////////////
	///		�QD�`��^�X�N
	////////////////////////////////////////////////

	render2DTask_.AddTask("Render2DTask1", TASK_MAIN2,
		[&]()
	{
		///�v���C���[��UI�`��
		playerUiRender_->Render();

		//���g���C�`��
		if (currentGameState_ == GAME_STATE::CLEAR || currentGameState_ == GAME_STATE::OVER)
		{
			CGraphicsUtilities::RenderString(20, 950, "F2�Ń��g���C");
			CGraphicsUtilities::RenderString(20, 1000, "F3�Ń^�C�g����");
		}

		//�Q�[���N���A�`��
		if (currentGameState_ == GAME_STATE::CLEAR)
		{
			CRectangle rect;
			font_.CalculateStringRect(0, 0, "�S���|��������������", rect);
			font_.RenderString(g_pGraphics->GetTargetWidth() * 0.5f - (rect.GetWidth() * 0.5f), g_pGraphics->GetTargetHeight() * 0.5f - (rect.GetHeight() * 0.5f), "�S���|��������������");
		}
	}
	);

}

void Scene::CBattleScene::RegisterAfterSpawn()
{
	////////////////////////////////////////////////
	///		�X�|�[�����ɓo�^����^�X�N
	////////////////////////////////////////////////

	updateTask_.AddTask("AfterSpawnUpdate", TASK_MAIN1,
		[&]()
	{
		

		//�G�X�|�i�[�X�V
		for (size_t i = 0; i < enemySpawner_->size(); i++)
		{
			enemySpawner_->at(i)->Update(enemyManager_.GetEnemy(i));
		}
		

		//�G�X�V
		enemyManager_.Update();

		//�X�e�[�W�N���A����
		if (stageManager_.IsClear(clearTermProvider_))
		{
			if (currentGameState_ == GAME_STATE::NOMAL)
			{
				player_->ClearPose();
				currentGameState_ = GAME_STATE::CLEAR;
			}
		}
		//�X�e�[�W�̋����N���A���Ă���Ȃ�
		else if (stageManager_.GetCurrentDivision()->IsClear(clearTermProvider_) && 
				 currentGameState_ == GAME_STATE::NOMAL)
		{
			updateTask_.DeleteTask("AfterSpawnUpdate");
			updateTask_.DeleteTask("AfterSpawnCollision");
			renderTask_.DeleteTask("AfterSpawnRender");
			render2DTask_.DeleteTask("AfterSpawnRender2D");

			//���̋���
			stageManager_.NextPhase();

			//�G�𐶐�����
			enemyCreateThread_.Create([this]() { return CreateEnemys(); },
										[this]() {RegisterAfterSpawn(); }
										);
			//�^�C�}�[�����Z�b�g
			timer_.Start();
		}


		//�X�e�[�W�X�V
		stageManager_.Update();
	});

	//�G�̏Փ˔���
	updateTask_.AddTask("AfterSpawnCollision", TASK_COLLISION,
		[&]()
		{
			//�G�̓����蔻��
			for (size_t i = 0; i < enemyManager_.GetEnemyMaxCount(); i++)
			{
				EnemyPtr enemy = enemyManager_.GetEnemy(i);
				if (!enemy->IsShow())
				{
					continue;
				}
				//�G�ƃv���C���[
				CCollision::CollisionObj(player_, enemy);

				if (!enemy->IsInvincible())
				{
					//�G�ƒe
					for (int j = 0; j < ShotManagerInstance.GetShotCount(); j++)
					{
						auto shot = ShotManagerInstance.GetShot(j);
						CCollision::CollisionObj(shot, enemy);
					}
				}

				//�G�ƃI�u�W�F�N�g
				for (size_t j = 0; j < stageManager_.GetCurrentDivision()->GetObjCount(); j++)
				{
					auto obj = stageManager_.GetCurrentDivision()->GetObj(j);
					CCollision::CollisionObj(enemy, obj);
				}
			}
		}
		);

	//�G�̕`��
	renderTask_.AddTask("AfterSpawnRender", TASK_MAIN1,
		[&]()
	{
		//�G�`��
		enemyManager_.Render();
	}
	);

	//�GHP�`��
	render2DTask_.AddTask("AfterSpawnRender2D", TASK_MAIN1,
		[&]()
	{
		//HP�o�[�`��
		npcHpRender_.Render();
		//2DHP�o�[�`��
		npcHpRender_.Render2D();
	}
	);
}