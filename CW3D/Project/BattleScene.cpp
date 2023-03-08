#include "BattleScene.h"
#include "HPPresenter.h"
#include "SkillPresenter.h"
#include	"NormalCamera.h"

#include	"ActorObjectManager.h"
#include	"Stage1.h"
#include	"JsonStageLoader.h"	


using namespace ActionGame;



Scene::CBattleScene::CBattleScene()
	: player_(std::make_shared<CPlayer>())
	, enemyManager_()
	, enemySpawner_(std::make_shared<Spawner::EnemySpawnerArray>())
	, currentGameState_(GAME_STATE::NOMAL)
	, playerUiRender_()
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

	
	//UI�e�N�X�`���ǂݍ���
	if (ActionGame::CBattleUILoader::Load() == false)
	{
		return false;
	}
	//�v���C���[�ǂݍ���
	auto input = InputManagerInstance.GetInput(0);
	player_->SetInput(input);
	if (player_->Load() == false)
	{
		return false;
	}
	//�J�����ǂݍ���
	CameraPtr camera = std::make_shared<CNormalCamera>(player_->GetPosition(), player_->GetPosition(),Vector3(0,0,0), Vector3(0, 0, 0));
	CameraControllerInstance.Load(camera);

	//�G�t�F�N�g�ǂݍ���
	EffectRendererInstance.Initialize();
	if (ActionGame::EffectLoader::Load() == false)
	{
		return false;
	}

	//�X�e�[�W���ǂݍ���
	JsonStageLoader stageLoader;
	if (stageLoader.Load("Text/Stage1.json") == false)
	{
		return false;
	}
	
	//�X�e�[�W�ǂݍ���
	StagePtr stage = std::make_shared<CStage1>();
	stageManager_.Load(stage, stageLoader.GetDivisionArray());


	//�T�[�r�X���P�[�^�[�̐ݒ�
	ServiceLocator<CPlayer>::SetService(player_);

	//�v���C���[UI�ǂݍ���
	playerUiRender_.Load();
	CHPPresenter::Present(player_, playerUiRender_.GetHPRender());



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
	playerUiRender_.Initialize();

	//�N���A�����̃v���o�C�_�[�ɃI�u�U�[�o�[��o�^
	clearTermProvider_ = std::make_shared<ClearTerm::CProvider>();
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

	CGraphicsUtilities::RenderString(400, 0, "�^�C���X�P�[���F%.2f", TimeScaleControllerInstance.GetTimeScale(CHARA_TYPE::ENEMY));
	Vector2 pos;
	g_pInput->GetMousePos(pos);
	CGraphicsUtilities::RenderString(400, 30, "X:%.1f Y:%.1f", pos.x, pos.y);

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
	playerUiRender_.Release();

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
	size_t enemyCount = division->GetEnemyCount();

	//�N���A�����ɓG�̐���ݒ�
	clearTermProvider_->SetEnemyMaxCount(enemyCount);

	//�{�X���擾
	size_t bossCount = 0;
	for (auto param : *enemysParam)
	{
		if (param->GetParam().isBoss_)
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
		if (enemysParam->at(i)->GetParam().isBoss_)
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

