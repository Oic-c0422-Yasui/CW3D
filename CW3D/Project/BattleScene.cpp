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
	


	//メッシュ読み込み
	std::shared_ptr<CMeshContainer> tempMesh = std::make_shared<CMeshContainer>();
	if (tempMesh->Load("chara.mom") != MOFMODEL_RESULT_SUCCEEDED)
	{
		return false;
	}
	ResourcePtrManager<CMeshContainer>::GetInstance().AddResource("Player", "Player", tempMesh);

	
	//テクスチャ読み込み
	if (!m_UICreater.Create())
	{
		return false;
	}

	//エフェクト読み込み
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

	//ステージ情報読み込み
	JsonStageLoader stageLoader;
	stageLoader.Load("Text/Stage1.json");
	//ステージ読み込み
	StagePtr stage = std::make_shared<CStage1>();
	m_StageManager.Load(stage, stageLoader.GetDivisionArray());


	//プレイヤー読み込み
	auto input = InputManagerInstance.GetInput(0);
	m_Player->SetInput(input);
	if (!m_Player->Load())
	{
		return false;
	}
	//サービスロケーターの設定
	ServiceLocator<CPlayer>::SetService(m_Player);

	//プレイヤーUI読み込み
	m_PlayerUIRender = std::make_shared<CPlayerUIRender>();
	m_PlayerUIRender->Load();
	CHPPresenter::Present(m_Player, m_PlayerUIRender->GetHPRender());


	//カメラ読み込み
	CameraPtr camera = std::make_shared<NomalCamera>(m_Player->GetPosition(), m_Player->GetPosition(),Vector3(0,0,0), Vector3(0, 0, 0));
	CameraControllerInstance.Load(camera);

	//プレイヤーをマネージャーに登録
	ActorObjectManagerInstance.Add(m_Player);
	
	//フォント作成
	m_Font.Create(225, "ＭＳ ゴシック");

	return true;
}

void CBattleScene::Initialize()
{
	//インスタンスリセット
	EffectControllerInstance.Reset();
	ShotManagerInstance.Reset();
	CameraControllerInstance.SetDefault();
	TimeScaleControllerInstance.Reset();
	
	//タスクリセット
	m_UpdateTask.DeleteAllTaskImmediate();
	m_RenderTask.DeleteAllTaskImmediate();
	m_Render2DTask.DeleteAllTaskImmediate();

	//タイマー開始
	m_Timer.Start();

	//ステージマネージャー初期化
	m_StageManager.Initialize();

	//プレイヤー初期化
	m_Player->Initialize();
	m_PlayerUIRender->Initialize();

	//クリア条件のプロバイダーにオブザーバーを登録
	m_ClearTermProvider = std::make_shared<ClearTermProvider>();
	auto& provider = m_ClearTermProvider;
	m_EnemyManager.GetEnemyCountSubject().Subscribe([provider](size_t count) {provider->SetEnemyCount(count); });
	m_EnemyManager.GetBossCountSubject().Subscribe([provider](size_t count) {provider->SetBossCount(count); });
	m_Timer.GetTimeSubject().Subscribe([provider](float time) { provider->SetDivisionTime(time); });
	
	//敵生成
	m_EnemyCreateThread.Create( [this]() { return CreateEnemys(); },
								[this]() {RegisterAfterSpawn(); }
								);
	
	//ライト設定
	m_Light.SetDirection(Vector3(0.0f, -1.0f, 1.0f));
	CGraphicsUtilities::SetDirectionalLight(&m_Light);
	m_Light.SetAmbient(MOF_XRGB(255, 255, 255));
	m_Light.SetDiffuse(MOF_XRGB(220, 220, 220));
	m_Light.SetSpeculer(MOF_XRGB(255, 255, 255));

	//ゲームの状態初期化
	m_CurrentGameState = GAME_STATE::NOMAL;


	//タスクの登録
	RegisterTask();

}
void CBattleScene::Update()
{

	if (m_CurrentGameState == GAME_STATE::CLEAR || 
		m_CurrentGameState == GAME_STATE::OVER)
	{
		//遷移
		if (InputManagerInstance.GetInput(0)->IsPush(INPUT_KEY_BACK))
		{
			//タイトルへ遷移
			SceneChangeService::GetService()->ChangeScene(SCENENO::TITLE);
			return;
		}
	}

	//更新タスク実行
	m_UpdateTask.Excution();


	//エフェクト描画更新
	EffectRendererInstance.Update();
	//エフェクト操作更新
	EffectControllerInstance.Update();
	//時間操作更新
	TimeScaleControllerInstance.Update();
	//カメラ操作更新
	CameraControllerInstance.Update(m_Player->GetPosition(), m_Player->GetPosition());
	//ショットマネージャー更新
	ShotManagerInstance.Update();

	//ショット削除処理
	ShotManagerInstance.Delete();
	//エフェクト削除処理
	EffectControllerInstance.Delete();
	//アクター削除処理
	ActorObjectManagerInstance.Delete();
	
}

void CBattleScene::Render()
{
	//描画タスク実行
	m_RenderTask.Excution();

}

void CBattleScene::RenderDebug()
{
	//ステージデバッグ描画
	m_StageManager.RenderDebug();

	//ショットデバッグ描画
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
	//プレイヤー当たり判定デバッグ描画
	CGraphicsUtilities::RenderBox(m_Player->GetCollider(), Vector4(0, 1, 0, 0.2f));
	//プレイヤー回避時当たり判定デバッグ描画
	if (m_Player->IsEscape())
	{
		CGraphicsUtilities::RenderBox(m_Player->GetEscapeCollider(), Vector4(0, 0, 1, 0.2f));
	}
	if (m_EnemyCreateThread.IsComplete())
	{
		//敵当たり判定デバッグ描画
		m_EnemyManager.RenderDebug();
	}
}

void CBattleScene::Render2D()
{
	//２D描画タスク実行
	m_Render2DTask.Excution();

}

void CBattleScene::Render2DDebug()
{
	CGraphicsUtilities::RenderString(0, 0, "POS X:%.2f,Z:%.2f", m_Player->GetPosition().x, m_Player->GetPosition().z);
	CGraphicsUtilities::RenderString(0, 30, "VEL X:%.2f,Z:%.2f", m_Player->GetVelocity().x, m_Player->GetVelocity().z);

	CGraphicsUtilities::RenderString(0, 60, "角度：%.2f", MOF_ToDegree(m_Player->GetRotate().y));
	CGraphicsUtilities::RenderString(0, 90, m_Player->IsReverse() ? "向き：左" :"向き：右");

	CGraphicsUtilities::RenderString(400, 0, "タイムスケール：%.2f", TimeScaleControllerInstance.GetTimeScale());
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
	//アクターマネージャー解放
	ActorObjectManagerInstance.Release();
	//アクターID解放
	IDManagerInstance.Release();

	//ステージ解放
	m_StageManager.Release();

	//プレイヤー解放
	m_Player->Release();
	m_Player.reset();
	ServiceLocator<CPlayer>::Release();
	m_PlayerUIRender.reset();

	//敵解放
	m_EnemyManager.Release();
	m_EnemySpawner.reset();

	//HPバー解放
	m_NPCHPRender.Release();
	
	//リソース解放
	ActionGame::ResourceManager<Effekseer::EffectRef>::GetInstance().Release();
	ActionGame::ResourcePtrManager<CMeshContainer>::GetInstance().Release();
	ActionGame::ResourcePtrManager<CSprite3D>::GetInstance().Release();
	ActionGame::ResourcePtrManager<CTexture>::GetInstance().Release();
	ActionGame::ResourcePtrManager<CFont>::GetInstance().Release();


	//ショット解放
	ShotManagerInstance.Reset();
	ShotManagerInstance.Release();

	//エフェクト解放
	EffectRendererInstance.Release();
	EffectControllerInstance.Release();

	//タイムスケール解放
	TimeScaleControllerInstance.Release();

	//カメラ解放
	CameraControllerInstance.Release();
}

bool CBattleScene::CreateEnemys()
{
	//配列初期化
	m_EnemyManager.ClearEnemyArray();
	m_NPCHPRender.Reset();
	for (auto spawner : *m_EnemySpawner)
	{
		spawner->Reset();
	}

	//現在の区画から敵の情報を受け取る
	auto division = m_StageManager.GetCurrentDivision();
	auto enemysParam = division->GetEnemysParam();
	int enemyCount = division->GetEnemyCount();

	//クリア条件に敵の数を設定
	m_ClearTermProvider->SetEnemyMaxCount(enemyCount);

	//ボス数取得
	size_t bossCount = 0;
	for (auto param : *enemysParam)
	{
		if (param->GetParam().m_IsBoss)
		{
			bossCount++;
		}
	}

	//クリア条件にボスの数を設定
	m_ClearTermProvider->SetBossMaxCount(enemyCount);

	//敵のスポナー取得
	auto spawner = division->GetEnemySpawners();
	m_EnemySpawner = spawner;
	


	//敵のビルダーの辞書
	EnemyBuilderDictionary dictionary;

	for (int i = 0; i < enemyCount; i++)
	{
		//敵のタイプに合ったビルダーを取得
		auto builder = dictionary.Get(enemysParam->at(i)->GetParam().m_Type);

		//敵を追加する
		m_EnemyManager.AddEnemy(builder->Create(enemysParam->at(i)));

		//敵をマネージャーに登録
		ActorObjectManagerInstance.Add(m_EnemyManager.GetEnemy(i));
		//敵のHPバー生成＆オブザーバに登録
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

	//更新タスク登録
	RegisterUpdateTask();

	//衝突タスク登録
	RegisterCollisionTask();

	//描画タスク登録
	RegisterRenderTask();

	//２D描画タスク登録
	RegisterRender2DTask();

}

void CBattleScene::RegisterUpdateTask()
{
	////////////////////////////////////////////////
	///		更新タスク
	////////////////////////////////////////////////

	//リトライタスク
	m_UpdateTask.AddTask("RetryTask", TASK_EVENT,
		[&]()
	{
		//リトライ
		if (InputManagerInstance.GetInput(0)->IsPush(INPUT_KEY_RETRY))
		{
			//フェード
			auto sceneEffect = std::make_shared<ActionGame::SceneChangeFade>(0.5f,0.5f,0.5f);
			//初期化
			SceneInitializeService::GetService()->InitializeScene(sceneEffect);
			return;
		}
		
	}
	);
	//更新タスク
	m_UpdateTask.AddTask("UpdateTask1", TASK_MAIN1,
		[&]()
	{
		
		//タイマー更新
		m_Timer.Update();

		//プレイヤー更新
		m_Player->Update();
	}
	);

	//条件の設定タスク
	m_UpdateTask.AddTask("SetConditionTask", TASK_MAIN2,
		[&]()
	{

		//死亡判定
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
	///		当たり判定タスク
	////////////////////////////////////////////////

	m_UpdateTask.AddTask("CollisionTask1", TASK_COLLISION,
		[&]()
	{
		if (m_CurrentGameState == GAME_STATE::NOMAL)
		{
			//プレイヤーとオブジェクトの当たり判定
			for (size_t i = 0; i < m_StageManager.GetCurrentDivision()->GetObjCount(); i++)
			{
				auto obj = m_StageManager.GetCurrentDivision()->GetObj(i);
				CCollision::CollisionObj(m_Player, obj);
			}

			//プレイヤーと弾の当たり判定
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
	///		描画タスク
	////////////////////////////////////////////////

	m_RenderTask.AddTask("RenderTask1", TASK_MAIN1,
		[&]()
	{
		//ステージ描画
		m_StageManager.Render();

		//プレイヤー描画
		m_Player->Render();

	}
	);
	m_RenderTask.AddTask("RenderTask2", TASK_MAIN3,
		[&]()
		{
			//ショット描画
			ShotManagerInstance.Render();
			//エフェクト描画
			EffectRendererInstance.Render();
		}
		);
}

void CBattleScene::RegisterRender2DTask()
{
	////////////////////////////////////////////////
	///		２D描画タスク
	////////////////////////////////////////////////

	m_Render2DTask.AddTask("Render2DTask1", TASK_MAIN2,
		[&]()
	{
		///プレイヤーのUI描画
		m_PlayerUIRender->Render();

		//リトライ描画
		if (m_CurrentGameState == GAME_STATE::CLEAR || m_CurrentGameState == GAME_STATE::OVER)
		{
			CGraphicsUtilities::RenderString(20, 950, "F2でリトライ");
			CGraphicsUtilities::RenderString(20, 1000, "F3でタイトルへ");
		}

		//ゲームクリア描画
		if (m_CurrentGameState == GAME_STATE::CLEAR)
		{
			CRectangle rect;
			m_Font.CalculateStringRect(0, 0, "全部倒したあああああ", rect);
			m_Font.RenderString(g_pGraphics->GetTargetWidth() * 0.5f - (rect.GetWidth() * 0.5f), g_pGraphics->GetTargetHeight() * 0.5f - (rect.GetHeight() * 0.5f), "全部倒したあああああ");
		}
	}
	);

}

void CBattleScene::RegisterAfterSpawn()
{
	////////////////////////////////////////////////
	///		スポーン時に登録するタスク
	////////////////////////////////////////////////

	m_UpdateTask.AddTask("AfterSpawnUpdate", TASK_MAIN1,
		[&]()
	{
		

		//敵スポナー更新
		for (size_t i = 0; i < m_EnemySpawner->size(); i++)
		{
			m_EnemySpawner->at(i)->Update(m_EnemyManager.GetEnemy(i));
		}
		

		//敵更新
		m_EnemyManager.Update();

		//ステージクリア判定
		if (m_StageManager.IsClear(m_ClearTermProvider))
		{
			if (m_CurrentGameState == GAME_STATE::NOMAL)
			{
				m_Player->ClearPose();
				m_CurrentGameState = GAME_STATE::CLEAR;
			}
		}
		//ステージの区画をクリアしているなら
		else if (m_StageManager.GetCurrentDivision()->IsClear(m_ClearTermProvider) && 
				 m_CurrentGameState == GAME_STATE::NOMAL)
		{
			m_UpdateTask.DeleteTask("AfterSpawnUpdate");
			m_UpdateTask.DeleteTask("AfterSpawnCollision");
			m_RenderTask.DeleteTask("AfterSpawnRender");
			m_Render2DTask.DeleteTask("AfterSpawnRender2D");

			//次の区画へ
			m_StageManager.NextPhase();

			//敵を生成する
			m_EnemyCreateThread.Create([this]() { return CreateEnemys(); },
										[this]() {RegisterAfterSpawn(); }
										);
			//タイマーをリセット
			m_Timer.Start();
		}


		//ステージ更新
		m_StageManager.Update();
	});

	//敵の衝突判定
	m_UpdateTask.AddTask("AfterSpawnCollision", TASK_COLLISION,
		[&]()
		{
			//敵の当たり判定
			for (size_t i = 0; i < m_EnemyManager.GetEnemyMaxCount(); i++)
			{
				EnemyPtr enemy = m_EnemyManager.GetEnemy(i);
				if (!enemy->IsShow())
				{
					continue;
				}
				//敵とプレイヤー
				CCollision::CollisionObj(m_Player, enemy);

				if (!enemy->IsInvincible())
				{
					//敵と弾
					for (int j = 0; j < ShotManagerInstance.GetShotCount(); j++)
					{
						auto shot = ShotManagerInstance.GetShot(j);
						CCollision::CollisionObj(shot, enemy);
					}
				}

				//敵とオブジェクト
				for (size_t j = 0; j < m_StageManager.GetCurrentDivision()->GetObjCount(); j++)
				{
					auto obj = m_StageManager.GetCurrentDivision()->GetObj(j);
					CCollision::CollisionObj(enemy, obj);
				}
			}
		}
		);

	//敵の描画
	m_RenderTask.AddTask("AfterSpawnRender", TASK_MAIN1,
		[&]()
	{
		//敵描画
		m_EnemyManager.Render();
	}
	);

	//敵HP描画
	m_Render2DTask.AddTask("AfterSpawnRender2D", TASK_MAIN1,
		[&]()
	{
		//HPバー描画
		m_NPCHPRender.Render();
		//2DHPバー描画
		m_NPCHPRender.Render2D();
	}
	);
}