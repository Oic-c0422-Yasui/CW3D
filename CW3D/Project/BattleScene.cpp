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



CBattleScene::CBattleScene()
	: m_Player(std::make_shared<CPlayer>())
	, m_EnemyManager()
	, m_EnemySpawner(std::make_shared<Spawner::EnemySpawnerArray>())
	, m_CurrentGameState(GAME_STATE::NOMAL)
{
}

CBattleScene::~CBattleScene()
{
}

bool CBattleScene::Load()
{
	


	//���b�V���ǂݍ���
	std::shared_ptr<CMeshContainer> tempMesh = std::make_shared<CMeshContainer>();
	if (tempMesh->Load("chara.mom") != MOFMODEL_RESULT_SUCCEEDED)
	{
		return false;
	}
	ResourcePtrManager<CMeshContainer>::GetInstance().AddResource("Player", "Player", tempMesh);

	
	//�e�N�X�`���ǂݍ���
	if (!m_UICreater.Create())
	{
		return false;
	}

	//�G�t�F�N�g�ǂݍ���
	EffectRendererInstance.Initialize();
	Effekseer::EffectRef effect = Effekseer::Effect::Create(EffectRendererInstance.GetManager(), u"Effect/Laser01.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResource("Effect", "Effect1", effect);
	effect = Effekseer::Effect::Create(EffectRendererInstance.GetManager(), u"Effect/sword.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResource("Effect", "DamageEffect1", effect);
	effect = Effekseer::Effect::Create(EffectRendererInstance.GetManager(), u"Effect/tuki.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResource("Effect", "Effect2", effect);
	effect = Effekseer::Effect::Create(EffectRendererInstance.GetManager(), u"Effect/sandStome.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResource("Effect", "Effect3", effect);
	effect = Effekseer::Effect::Create(EffectRendererInstance.GetManager(), u"Effect/Laser01.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResource("Effect", "Effect4", effect);
	effect = Effekseer::Effect::Create(EffectRendererInstance.GetManager(), u"Effect/tornade.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResource("Effect", "Effect5", effect);
	effect = Effekseer::Effect::Create(EffectRendererInstance.GetManager(), u"Effect/fire.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResource("Effect", "Effect6", effect);
	effect = Effekseer::Effect::Create(EffectRendererInstance.GetManager(), u"Effect/drill.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResource("Effect", "Effect7", effect);
	effect = Effekseer::Effect::Create(EffectRendererInstance.GetManager(), u"Effect/Track.efk");
	ResourceManager<Effekseer::EffectRef>::GetInstance().AddResource("Effect", "ClosedEffect", effect);

	//�X�e�[�W���ǂݍ���
	JsonStageLoader stageLoader;
	stageLoader.Load("Text/Stage1.json");
	//�X�e�[�W�ǂݍ���
	StagePtr stage = std::make_shared<CStage1>();
	m_StageManager.Load(stage, stageLoader.GetDivisionArray());


	//�v���C���[�ǂݍ���
	auto input = InputManagerInstance.GetInput(0);
	m_Player->SetInput(input);
	if (!m_Player->Load())
	{
		return false;
	}
	//�T�[�r�X���P�[�^�[�̐ݒ�
	ServiceLocator<CPlayer>::SetService(m_Player);

	//�v���C���[UI�ǂݍ���
	m_PlayerUIRender = std::make_shared<CPlayerUIRender>();
	m_PlayerUIRender->Load();
	CHPPresenter::Present(m_Player, m_PlayerUIRender->GetHPRender());


	//�J�����ǂݍ���
	CameraPtr camera = std::make_shared<NomalCamera>(m_Player->GetPosition(), m_Player->GetPosition(),Vector3(0,0,0), Vector3(0, 0, 0));
	CameraControllerInstance.Load(camera);

	//�v���C���[���}�l�[�W���[�ɓo�^
	ActorObjectManagerInstance.Add(m_Player);
	
	//�t�H���g�쐬
	m_Font.Create(225, "�l�r �S�V�b�N");

	return true;
}

void CBattleScene::Initialize()
{
	//�C���X�^���X���Z�b�g
	EffectControllerInstance.Reset();
	ShotManagerInstance.Reset();
	CameraControllerInstance.SetDefault();
	TimeScaleControllerInstance.Reset();
	
	//�^�X�N���Z�b�g
	m_UpdateTask.DeleteAllTaskImmediate();
	m_RenderTask.DeleteAllTaskImmediate();
	m_Render2DTask.DeleteAllTaskImmediate();

	//�^�C�}�[�J�n
	m_Timer.Start();

	//�X�e�[�W�}�l�[�W���[������
	m_StageManager.Initialize();

	//�v���C���[������
	m_Player->Initialize();
	m_PlayerUIRender->Initialize();

	//�N���A�����̃v���o�C�_�[�ɃI�u�U�[�o�[��o�^
	m_ClearTermProvider = std::make_shared<ClearTermProvider>();
	auto& provider = m_ClearTermProvider;
	m_EnemyManager.GetEnemyCountSubject().Subscribe([provider](size_t count) {provider->SetEnemyCount(count); });
	m_EnemyManager.GetBossCountSubject().Subscribe([provider](size_t count) {provider->SetBossCount(count); });
	m_Timer.GetTimeSubject().Subscribe([provider](float time) { provider->SetDivisionTime(time); });
	
	//�G����
	m_EnemyCreateThread.Create( [this]() { return CreateEnemys(); },
								[this]() {RegisterAfterSpawn(); }
								);
	
	//���C�g�ݒ�
	m_Light.SetDirection(Vector3(0.0f, -1.0f, 1.0f));
	CGraphicsUtilities::SetDirectionalLight(&m_Light);
	m_Light.SetAmbient(MOF_XRGB(255, 255, 255));
	m_Light.SetDiffuse(MOF_XRGB(220, 220, 220));
	m_Light.SetSpeculer(MOF_XRGB(255, 255, 255));

	//�Q�[���̏�ԏ�����
	m_CurrentGameState = GAME_STATE::NOMAL;


	//�^�X�N�̓o�^
	RegisterTask();

}
void CBattleScene::Update()
{

	if (m_CurrentGameState == GAME_STATE::CLEAR || 
		m_CurrentGameState == GAME_STATE::OVER)
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
	m_UpdateTask.Excution();


	//�G�t�F�N�g�`��X�V
	EffectRendererInstance.Update();
	//�G�t�F�N�g����X�V
	EffectControllerInstance.Update();
	//���ԑ���X�V
	TimeScaleControllerInstance.Update();
	//�J��������X�V
	CameraControllerInstance.Update(m_Player->GetPosition(), m_Player->GetPosition());
	//�V���b�g�}�l�[�W���[�X�V
	ShotManagerInstance.Update();

	//�V���b�g�폜����
	ShotManagerInstance.Delete();
	//�G�t�F�N�g�폜����
	EffectControllerInstance.Delete();
	//�A�N�^�[�폜����
	ActorObjectManagerInstance.Delete();
	
}

void CBattleScene::Render()
{
	//�`��^�X�N���s
	m_RenderTask.Excution();

}

void CBattleScene::RenderDebug()
{
	//�X�e�[�W�f�o�b�O�`��
	m_StageManager.RenderDebug();

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
	CGraphicsUtilities::RenderBox(m_Player->GetCollider(), Vector4(0, 1, 0, 0.2f));
	//�v���C���[����������蔻��f�o�b�O�`��
	if (m_Player->IsEscape())
	{
		CGraphicsUtilities::RenderBox(m_Player->GetEscapeCollider(), Vector4(0, 0, 1, 0.2f));
	}
	if (m_EnemyCreateThread.IsComplete())
	{
		//�G�����蔻��f�o�b�O�`��
		m_EnemyManager.RenderDebug();
	}
}

void CBattleScene::Render2D()
{
	//�QD�`��^�X�N���s
	m_Render2DTask.Excution();

}

void CBattleScene::Render2DDebug()
{
	CGraphicsUtilities::RenderString(0, 0, "POS X:%.2f,Z:%.2f", m_Player->GetPosition().x, m_Player->GetPosition().z);
	CGraphicsUtilities::RenderString(0, 30, "VEL X:%.2f,Z:%.2f", m_Player->GetVelocity().x, m_Player->GetVelocity().z);

	CGraphicsUtilities::RenderString(0, 60, "�p�x�F%.2f", MOF_ToDegree(m_Player->GetRotate().y));
	CGraphicsUtilities::RenderString(0, 90, m_Player->IsReverse() ? "�����F��" :"�����F�E");

	CGraphicsUtilities::RenderString(400, 0, "�^�C���X�P�[���F%.2f", TimeScaleControllerInstance.GetTimeScale());
	Vector2 pos;
	g_pInput->GetMousePos(pos);
	CGraphicsUtilities::RenderString(400, 30, "X:%.1f Y:%.1f", pos.x, pos.y);
	if (m_EnemyCreateThread.IsComplete())
	{
		CGraphicsUtilities::RenderString(10, 180, m_EnemyManager.GetEnemy(0)->GetName().c_str());
	}

}

void CBattleScene::Release()
{
	//�A�N�^�[�}�l�[�W���[���
	ActorObjectManagerInstance.Release();
	//�A�N�^�[ID���
	IDManagerInstance.Release();

	//�X�e�[�W���
	m_StageManager.Release();

	//�v���C���[���
	m_Player->Release();
	m_Player.reset();
	ServiceLocator<CPlayer>::Release();
	m_PlayerUIRender.reset();

	//�G���
	m_EnemyManager.Release();
	m_EnemySpawner.reset();

	//HP�o�[���
	m_NPCHPRender.Release();
	
	//���\�[�X���
	ActionGame::ResourceManager<Effekseer::EffectRef>::GetInstance().Release();
	ActionGame::ResourcePtrManager<CMeshContainer>::GetInstance().Release();
	ActionGame::ResourcePtrManager<CSprite3D>::GetInstance().Release();
	ActionGame::ResourcePtrManager<CTexture>::GetInstance().Release();
	ActionGame::ResourcePtrManager<CFont>::GetInstance().Release();


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

bool CBattleScene::CreateEnemys()
{
	//�z�񏉊���
	m_EnemyManager.ClearEnemyArray();
	m_NPCHPRender.Reset();
	for (auto spawner : *m_EnemySpawner)
	{
		spawner->Reset();
	}

	//���݂̋�悩��G�̏����󂯎��
	auto division = m_StageManager.GetCurrentDivision();
	auto enemysParam = division->GetEnemysParam();
	int enemyCount = division->GetEnemyCount();

	//�N���A�����ɓG�̐���ݒ�
	m_ClearTermProvider->SetEnemyMaxCount(enemyCount);

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
	m_ClearTermProvider->SetBossMaxCount(enemyCount);

	//�G�̃X�|�i�[�擾
	auto spawner = division->GetEnemySpawners();
	m_EnemySpawner = spawner;
	


	//�G�̃r���_�[�̎���
	EnemyBuilderDictionary dictionary;

	for (int i = 0; i < enemyCount; i++)
	{
		//�G�̃^�C�v�ɍ������r���_�[���擾
		auto builder = dictionary.Get(enemysParam->at(i)->GetParam().m_Type);

		//�G��ǉ�����
		m_EnemyManager.AddEnemy(builder->Create(enemysParam->at(i)));

		//�G���}�l�[�W���[�ɓo�^
		ActorObjectManagerInstance.Add(m_EnemyManager.GetEnemy(i));
		//�G��HP�o�[�������I�u�U�[�o�ɓo�^
		if (enemysParam->at(i)->GetParam().m_IsBoss)
		{
			auto bossHP = std::make_shared<BossHPRender>();
			CHPPresenter::Present(m_EnemyManager.GetEnemy(i), bossHP);
			m_NPCHPRender.Add(bossHP);
		}
		else
		{
			auto normalHP = std::make_shared<NormalEnemyHPRender>();
			CHPPresenter::Present(m_EnemyManager.GetEnemy(i), normalHP);
			m_NPCHPRender.Add(normalHP);
		}
		
	}

	m_NPCHPRender.Load();
	m_NPCHPRender.Initialize();

	return true;
}

void CBattleScene::RegisterTask()
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

void CBattleScene::RegisterUpdateTask()
{
	////////////////////////////////////////////////
	///		�X�V�^�X�N
	////////////////////////////////////////////////

	//���g���C�^�X�N
	m_UpdateTask.AddTask("RetryTask", TASK_EVENT,
		[&]()
	{
		//���g���C
		if (InputManagerInstance.GetInput(0)->IsPush(INPUT_KEY_RETRY))
		{
			//�t�F�[�h
			auto sceneEffect = std::make_shared<ActionGame::SceneChangeFade>(0.5f,0.5f,0.5f);
			//������
			SceneInitializeService::GetService()->InitializeScene(sceneEffect);
			return;
		}
		
	}
	);
	//�X�V�^�X�N
	m_UpdateTask.AddTask("UpdateTask1", TASK_MAIN1,
		[&]()
	{
		
		//�^�C�}�[�X�V
		m_Timer.Update();

		//�v���C���[�X�V
		m_Player->Update();
	}
	);

	//�����̐ݒ�^�X�N
	m_UpdateTask.AddTask("SetConditionTask", TASK_MAIN2,
		[&]()
	{

		//���S����
		if (!m_Player->IsShow() && m_Player->IsDead())
		{
			m_CurrentGameState = GAME_STATE::OVER;
		}

	}
	);

	
}

void CBattleScene::RegisterCollisionTask()
{

	////////////////////////////////////////////////
	///		�����蔻��^�X�N
	////////////////////////////////////////////////

	m_UpdateTask.AddTask("CollisionTask1", TASK_COLLISION,
		[&]()
	{
		if (m_CurrentGameState == GAME_STATE::NOMAL)
		{
			//�v���C���[�ƃI�u�W�F�N�g�̓����蔻��
			for (size_t i = 0; i < m_StageManager.GetCurrentDivision()->GetObjCount(); i++)
			{
				auto obj = m_StageManager.GetCurrentDivision()->GetObj(i);
				CCollision::CollisionObj(m_Player, obj);
			}

			//�v���C���[�ƒe�̓����蔻��
			for (size_t i = 0; i < ShotManagerInstance.GetShotCount(); i++)
			{
				auto shot = ShotManagerInstance.GetShot(i);
				CCollision::CollisionObj(shot, m_Player);
			}
		}
	}
	);

}

void CBattleScene::RegisterRenderTask()
{
	////////////////////////////////////////////////
	///		�`��^�X�N
	////////////////////////////////////////////////

	m_RenderTask.AddTask("RenderTask1", TASK_MAIN1,
		[&]()
	{
		//�X�e�[�W�`��
		m_StageManager.Render();

		//�v���C���[�`��
		m_Player->Render();

	}
	);
	m_RenderTask.AddTask("RenderTask2", TASK_MAIN3,
		[&]()
		{
			//�V���b�g�`��
			ShotManagerInstance.Render();
			//�G�t�F�N�g�`��
			EffectRendererInstance.Render();
		}
		);
}

void CBattleScene::RegisterRender2DTask()
{
	////////////////////////////////////////////////
	///		�QD�`��^�X�N
	////////////////////////////////////////////////

	m_Render2DTask.AddTask("Render2DTask1", TASK_MAIN2,
		[&]()
	{
		///�v���C���[��UI�`��
		m_PlayerUIRender->Render();

		//���g���C�`��
		if (m_CurrentGameState == GAME_STATE::CLEAR || m_CurrentGameState == GAME_STATE::OVER)
		{
			CGraphicsUtilities::RenderString(20, 950, "F2�Ń��g���C");
			CGraphicsUtilities::RenderString(20, 1000, "F3�Ń^�C�g����");
		}

		//�Q�[���N���A�`��
		if (m_CurrentGameState == GAME_STATE::CLEAR)
		{
			CRectangle rect;
			m_Font.CalculateStringRect(0, 0, "�S���|��������������", rect);
			m_Font.RenderString(g_pGraphics->GetTargetWidth() * 0.5f - (rect.GetWidth() * 0.5f), g_pGraphics->GetTargetHeight() * 0.5f - (rect.GetHeight() * 0.5f), "�S���|��������������");
		}
	}
	);

}

void CBattleScene::RegisterAfterSpawn()
{
	////////////////////////////////////////////////
	///		�X�|�[�����ɓo�^����^�X�N
	////////////////////////////////////////////////

	m_UpdateTask.AddTask("AfterSpawnUpdate", TASK_MAIN1,
		[&]()
	{
		

		//�G�X�|�i�[�X�V
		for (size_t i = 0; i < m_EnemySpawner->size(); i++)
		{
			m_EnemySpawner->at(i)->Update(m_EnemyManager.GetEnemy(i));
		}
		

		//�G�X�V
		m_EnemyManager.Update();

		//�X�e�[�W�N���A����
		if (m_StageManager.IsClear(m_ClearTermProvider))
		{
			if (m_CurrentGameState == GAME_STATE::NOMAL)
			{
				m_Player->ClearPose();
				m_CurrentGameState = GAME_STATE::CLEAR;
			}
		}
		//�X�e�[�W�̋����N���A���Ă���Ȃ�
		else if (m_StageManager.GetCurrentDivision()->IsClear(m_ClearTermProvider) && 
				 m_CurrentGameState == GAME_STATE::NOMAL)
		{
			m_UpdateTask.DeleteTask("AfterSpawnUpdate");
			m_UpdateTask.DeleteTask("AfterSpawnCollision");
			m_RenderTask.DeleteTask("AfterSpawnRender");
			m_Render2DTask.DeleteTask("AfterSpawnRender2D");

			//���̋���
			m_StageManager.NextPhase();

			//�G�𐶐�����
			m_EnemyCreateThread.Create([this]() { return CreateEnemys(); },
										[this]() {RegisterAfterSpawn(); }
										);
			//�^�C�}�[�����Z�b�g
			m_Timer.Start();
		}


		//�X�e�[�W�X�V
		m_StageManager.Update();
	});

	//�G�̏Փ˔���
	m_UpdateTask.AddTask("AfterSpawnCollision", TASK_COLLISION,
		[&]()
		{
			//�G�̓����蔻��
			for (size_t i = 0; i < m_EnemyManager.GetEnemyMaxCount(); i++)
			{
				EnemyPtr enemy = m_EnemyManager.GetEnemy(i);
				if (!enemy->IsShow())
				{
					continue;
				}
				//�G�ƃv���C���[
				CCollision::CollisionObj(m_Player, enemy);

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
				for (size_t j = 0; j < m_StageManager.GetCurrentDivision()->GetObjCount(); j++)
				{
					auto obj = m_StageManager.GetCurrentDivision()->GetObj(j);
					CCollision::CollisionObj(enemy, obj);
				}
			}
		}
		);

	//�G�̕`��
	m_RenderTask.AddTask("AfterSpawnRender", TASK_MAIN1,
		[&]()
	{
		//�G�`��
		m_EnemyManager.Render();
	}
	);

	//�GHP�`��
	m_Render2DTask.AddTask("AfterSpawnRender2D", TASK_MAIN1,
		[&]()
	{
		//HP�o�[�`��
		m_NPCHPRender.Render();
		//2DHP�o�[�`��
		m_NPCHPRender.Render2D();
	}
	);
}