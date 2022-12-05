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
#include	"StateInput.h"
#include	"ActorObjectManager.h"
#include	"Stage1.h"
#include	"JsonStageLoader.h"	


using namespace ActionGame;

using Task = std::function<void()>;
//std::vector<Task> taskList;

CBattleScene::CBattleScene()
	: m_Player(std::make_shared<CPlayer>())
	, m_EnemyManager()
	, m_GameClearFlg(false)
	, m_GameOverFlg(false)
	, m_EnemySpawner()
{
}

CBattleScene::~CBattleScene()
{
}

bool CBattleScene::Load()
{
	//�C���v�b�g�ǂݍ���
	auto input = InputManagerInstance.AddInput<ActionGame::MofInput>();
	InputManagerInstance.AddInput<ActionGame::StateInput>();

	//�L�[�{�[�h
	input->AddKeyboardKey(INPUT_KEY_HORIZONTAL, MOFKEY_RIGHT, MOFKEY_LEFT);
	input->AddKeyboardKey(INPUT_KEY_VERTICAL, MOFKEY_DOWN, MOFKEY_UP);
	input->AddKeyboardKey(INPUT_KEY_JUMP,MOFKEY_X);
	input->AddKeyboardKey(INPUT_KEY_ATTACK, MOFKEY_Z);
	input->AddKeyboardKey(INPUT_KEY_SKILL1, MOFKEY_D);
	input->AddKeyboardKey(INPUT_KEY_SKILL2, MOFKEY_A);
	input->AddKeyboardKey(INPUT_KEY_SKILL3, MOFKEY_S);
	input->AddKeyboardKey(INPUT_KEY_SKILL_DROPKICK, MOFKEY_F);
	input->AddKeyboardKey(INPUT_KEY_ESCAPE, MOFKEY_SPACE);
	input->AddKeyboardKey(INPUT_KEY_RETRY, MOFKEY_F2);
	//�p�b�h
	input->AddJoyStickHorizontal(INPUT_KEY_HORIZONTAL, 0);
	input->AddJoyStickVertical(INPUT_KEY_VERTICAL, 0);
	input->AddJoypadKey(INPUT_KEY_ATTACK, 0,0);


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


	//�J����������
	CameraPtr camera = std::make_shared<CNomalCamera>(m_Player->GetPosition(), m_Player->GetPosition(),Vector3(0,0,0), Vector3(0, 0, 0));
	CameraControllerInstance.Load(camera);

	//�v���C���[���}�l�[�W���[�ɓo�^
	ActorObjectManagerInstance.Add(m_Player);
	
	//�t�H���g�쐬
	m_Font.Create(225, "�l�r �S�V�b�N");

	return true;
}

void CBattleScene::Initialize()
{
	m_UpdateTask.ResetTask();
	m_RenderTask.ResetTask();
	m_Render2DTask.ResetTask();


	m_Timer.Start();

	m_StageManager.Initialize();

	m_Player->Initialize();
	m_PlayerUIRender->Initialize();

	//�N���A�����̃v���o�C�_�[�ɃI�u�U�[�o�[��o�^
	m_ClearTermProvider = std::make_shared<ClearTermProvider>();
	auto& provider = m_ClearTermProvider;
	m_EnemyManager.GetEnemyCountSubject().Subscribe([provider](size_t count) {provider->SetEnemyCount(count); });
	
	//�G����
	m_EnemyCreateThread.Create([this]() { return CreateEnemys(); },
								[this]() {RegisterAfterSpawn(); }
								);


	m_Timer.GetTimeSubject().Subscribe([provider](float time) { provider->SetDivisionTime(time); });
	
	//���C�g�ݒ�
	m_Light.SetDirection(Vector3(0.0f, -1.0f, 1.0f));
	CGraphicsUtilities::SetDirectionalLight(&m_Light);
	m_Light.SetAmbient(MOF_XRGB(255, 255, 255));
	m_Light.SetDiffuse(MOF_XRGB(220, 220, 220));
	m_Light.SetSpeculer(MOF_XRGB(255, 255, 255));

	m_GameClearFlg = false;
	m_GameOverFlg = false;

	EffectControllerInstance.Reset();
	ShotManagerInstance.Reset();
	CameraControllerInstance.SetDefault();
	TimeScaleControllerInstance.Reset();

	//�^�X�N�̓o�^
	RegisterTask();

}

void CBattleScene::Update()
{
	//���͍X�V
	InputManagerInstance.Update();

	//�X�V�^�X�N���s
	m_UpdateTask.Excution();


	//�G�t�F�N�g�}�l�[�W���[�X�V
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

		if (!shot->IsShow() || !shot->GetCollideFlg())
		{
			continue;
		}
		switch (shot->GetColliderType())
		{
		case COLLISION_SPHERE:
		{
			CGraphicsUtilities::RenderLineSphere(shot->GetColliderSphere(), Vector4(1, 0, 0, 0.2f));
			break;
		}
		case COLLISION_AABB:
		{
			CGraphicsUtilities::RenderBox(shot->GetColliderAABB(), Vector4(1, 0, 0, 0.2f)); 
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
	ServiceLocator<CPlayer>::GetInstance().Release();
	m_PlayerUIRender.reset();

	//�G���
	m_EnemyManager.Release();
	m_EnemySpawner.clear();
	for (int i = 0; i < m_EnemysHPRender.size(); i++)
	{
		m_EnemysHPRender[i].reset();
	}
	m_EnemysHPRender.clear();
	
	//���\�[�X���
	ActionGame::ResourceManager<Effekseer::EffectRef>::GetInstance().Release();
	ActionGame::ResourcePtrManager<CMeshContainer>::GetInstance().Release();
	ActionGame::ResourcePtrManager<CSprite3D>::GetInstance().Release();
	ActionGame::ResourcePtrManager<CTexture>::GetInstance().Release();
	ActionGame::ResourcePtrManager<CFont>::GetInstance().Release();

	//�C���v�b�g���(��)
	InputManagerInstance.Release();

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

void CBattleScene::Collision()
{
	//if (m_EnemyCreateThread.IsComplete())
	//{
	//	//�G�̓����蔻��
	//	for (size_t i = 0; i < m_EnemyManager.GetMaxEnemyCount(); i++)
	//	{
	//		EnemyPtr enemy = m_EnemyManager.GetEnemy(i);
	//		if (!enemy->IsShow())
	//		{
	//			continue;
	//		}
	//		//�G�ƃv���C���[
	//		CCollision::CollisionObj(m_Player, enemy);

	//		if (!enemy->IsInvincible())
	//		{
	//			//for (int j = i + 1; j < m_Enemys.size(); j++)
	//			//{
	//			//	//�G�ƓG
	//			//	CCollision::CollisionObj(m_Enemys[i], m_Enemys[j]);
	//			//}
	//			//�G�ƒe
	//			for (int j = 0; j < ShotManagerInstance.GetShotCount(); j++)
	//			{
	//				auto shot = ShotManagerInstance.GetShot(j);
	//				CCollision::CollisionObj(shot, enemy);
	//			}
	//		}

	//		//�G�ƃI�u�W�F�N�g
	//		for (size_t j = 0; j < m_StageManager.GetCurrentDivision()->GetObjCount(); j++)
	//		{
	//			auto obj = m_StageManager.GetCurrentDivision()->GetObj(j);
	//			CCollision::CollisionObj(enemy, obj);
	//		}
	//	}
	//}
	////�v���C���[�ƃI�u�W�F�N�g�̓����蔻��
	//for (size_t i = 0; i < m_StageManager.GetCurrentDivision()->GetObjCount(); i++)
	//{
	//	auto obj = m_StageManager.GetCurrentDivision()->GetObj(i);
	//	CCollision::CollisionObj(m_Player, obj);
	//}

	////�v���C���[�ƒe�̓����蔻��
	//for (size_t i = 0; i < ShotManagerInstance.GetShotCount(); i++)
	//{
	//	auto shot = ShotManagerInstance.GetShot(i);
	//	CCollision::CollisionObj(shot, m_Player);
	//}

	//
}

bool CBattleScene::CreateEnemys()
{
	//�z�񏉊���
	m_EnemyManager.ClearEnemyArray();
	m_EnemysHPRender.clear();
	m_EnemySpawner.clear();

	//���݂̋�悩��G�̏����󂯎��
	auto division = m_StageManager.GetCurrentDivision();
	auto enemysParam = division->GetEnemysParam();
	int enemyCount = division->GetEnemyCount();

	//�G�̐���ݒ�
	m_ClearTermProvider->SetEnemyMaxCount(enemyCount);

	//�G�̃r���_�[�̎���
	EnemyBuilderDictionary dictionary;

	//�X�|�[������
	Spawner::EnemySpawnConditionCountLimitPtr spawnCondition = std::make_shared<Spawner::EnemySpawnConditionCountLimit>(enemyCount);
	m_EnemyManager.GetEnemyCountSubject().Subscribe([spawnCondition](size_t count) {spawnCondition->SetCount(count); });

	//�G�X�|�i�[�̍쐬
	/*m_EnemySpawner.push_back(std::make_shared<Spawner::EnemySpawner>(
		Spawner::SpawnConditionArray{ spawnCondition },
		std::make_shared<Spawner::SpawnCycleFixedRange>(10),
		std::make_shared<Spawner::EnemySpawnParameter>(enemysParam),
		m_EnemyManager.));*/

	for (int i = 0; i < enemyCount; i++)
	{
		//�G�̃^�C�v�ɍ������r���_�[���擾
		auto builder = dictionary.Get(enemysParam->at(i)->GetParam().m_Type);

		//�G��ǉ�����
		m_EnemyManager.AddEnemy(builder->Create(enemysParam->at(i)));

		//�G���}�l�[�W���[�ɓo�^
		ActorObjectManagerInstance.Add(m_EnemyManager.GetEnemy(i));
		//�G��HP�o�[�������I�u�U�[�o�ɓo�^
		m_EnemysHPRender.push_back(std::make_shared<CEnemyHPRender>());
		CHPPresenter::Present(m_EnemyManager.GetEnemy(i), m_EnemysHPRender[i]);
		m_EnemysHPRender[i]->Initialize();
	}

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

		if (m_GameClearFlg || m_GameOverFlg)
		{
			//�Q�[���I�[�o�[OR�N���A���A���g���C�\
			if (InputManagerInstance.GetInput(0)->IsPush(INPUT_KEY_RETRY))
			{
				Initialize();
				return;
			}
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

		//�N���A����
		if (m_StageManager.IsClear())
		{
			if (!m_GameClearFlg)
			{
				m_Player->SetClearPose();
				m_GameClearFlg = true;
			}
		}

		//���S����
		if (!m_Player->IsShow() && m_Player->IsDead())
		{
			m_GameOverFlg = true;
		}

	}
	);

	
}

void CBattleScene::RegisterCollisionTask()
{

	////////////////////////////////////////////////
	///		�Փ˃^�X�N
	////////////////////////////////////////////////

	m_UpdateTask.AddTask("CollisionTask1", TASK_COLLISION,
		[&]()
	{
		if (!m_GameClearFlg && !m_GameOverFlg)
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
		if (m_GameClearFlg || m_GameOverFlg)
		{
			CGraphicsUtilities::RenderString(20, 1000, "F2�Ń��g���C");
		}

		//�Q�[���N���A�`��
		if (m_GameClearFlg)
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
	/*
	* �X�|�[�����ɓo�^����^�X�N
	*/

	m_UpdateTask.AddTask("AfterSpawnUpdate", TASK_MAIN1,
		[&]()
	{
		//�G�X�|�i�[�X�V
		for (auto spawner : m_EnemySpawner)
		{
			spawner.Update(m_EnemyManager);
		}

		//�G�X�V
		m_EnemyManager.Update();
		//�X�e�[�W�̋����N���A���Ă���Ȃ�
		if (m_StageManager.GetCurrentDivision()->IsClear() && !m_GameClearFlg)
		{
			m_UpdateTask.DeleteTask("AfterSpawnCollision");
			m_UpdateTask.DeleteTask("AfterSpawnUpdate");
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
		m_StageManager.Update(m_ClearTermProvider);
	});

	//�G�̏Փ˔���
	m_UpdateTask.AddTask("AfterSpawnCollision", TASK_COLLISION,
		[&]()
		{
			//�G�̓����蔻��
			for (size_t i = 0; i < m_EnemyManager.GetMaxEnemyCount(); i++)
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
					//for (int j = i + 1; j < m_Enemys.size(); j++)
					//{
					//	//�G�ƓG
					//	CCollision::CollisionObj(m_Enemys[i], m_Enemys[j]);
					//}
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
		//�GHP�o�[�̕`�����ւ�
		std::sort(m_EnemysHPRender.begin(), m_EnemysHPRender.end(),
			[](ActionGame::EnemyHPRenderPtr& obj1, ActionGame::EnemyHPRenderPtr& obj2)
		{
			return obj1->GetViewPosition().z > obj2->GetViewPosition().z;
		});

		//�G��HP�o�[�`��
		for (auto& enemyHP : m_EnemysHPRender)
		{
			enemyHP->Render();
		}
	}
	);
}