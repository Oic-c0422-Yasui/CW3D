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
	


	//メッシュ読み込み
	std::shared_ptr<CMeshContainer> tempMesh = std::make_shared<CMeshContainer>();
	if (tempMesh->Load("chara.mom") != MOFMODEL_RESULT_SUCCEEDED)
	{
		return false;
	}
	ResourcePtrManager<CMeshContainer>::GetInstance().AddResource("Player", "Player", tempMesh);

	
	//テクスチャ読み込み
	if (!uiCreater_.Create())
	{
		return false;
	}

	//エフェクト読み込み
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

	//ステージ情報読み込み
	JsonStageLoader stageLoader;
	stageLoader.Load("Text/Stage1.json");
	//ステージ読み込み
	StagePtr stage = std::make_shared<CStage1>();
	stageManager_.Load(stage, stageLoader.GetDivisionArray());


	//プレイヤー読み込み
	auto input = InputManagerInstance.GetInput(0);
	player_->SetInput(input);
	if (!player_->Load())
	{
		return false;
	}
	//サービスロケーターの設定
	ServiceLocator<CPlayer>::SetService(player_);

	//プレイヤーUI読み込み
	playerUiRender_ = std::make_shared<CPlayerUIRender>();
	playerUiRender_->Load();
	CHPPresenter::Present(player_, playerUiRender_->GetHPRender());


	//カメラ読み込み
	CameraPtr camera = std::make_shared<NomalCamera>(player_->GetPosition(), player_->GetPosition(),Vector3(0,0,0), Vector3(0, 0, 0));
	CameraControllerInstance.Load(camera);

	//プレイヤーをマネージャーに登録
	ActorObjectManagerInstance.Add(player_);
	
	//フォント作成
	font_.Create(225, "ＭＳ ゴシック");

	return true;
}

void Scene::CBattleScene::Initialize()
{
	//インスタンスリセット
	EffectControllerInstance.Reset();
	ShotManagerInstance.Reset();
	CameraControllerInstance.SetDefault();
	TimeScaleControllerInstance.Reset();
	
	//タスクリセット
	updateTask_.DeleteAllTaskImmediate();
	renderTask_.DeleteAllTaskImmediate();
	render2DTask_.DeleteAllTaskImmediate();

	//タイマー開始
	timer_.Start();

	//ステージマネージャー初期化
	stageManager_.Initialize();

	//プレイヤー初期化
	player_->Initialize();
	playerUiRender_->Initialize();

	//クリア条件のプロバイダーにオブザーバーを登録
	clearTermProvider_ = std::make_shared<ClearTermProvider>();
	auto& provider = clearTermProvider_;
	enemyManager_.GetEnemyCountSubject().Subscribe([provider](size_t count) {provider->SetEnemyCount(count); });
	enemyManager_.GetBossCountSubject().Subscribe([provider](size_t count) {provider->SetBossCount(count); });
	timer_.GetTimeSubject().Subscribe([provider](float time) { provider->SetDivisionTime(time); });
	
	//敵生成
	enemyCreateThread_.Create( [this]() { return CreateEnemys(); },
								[this]() {RegisterAfterSpawn(); }
								);
	
	//ライト設定
	light_.SetDirection(Vector3(0.0f, -1.0f, 1.0f));
	CGraphicsUtilities::SetDirectionalLight(&light_);
	light_.SetAmbient(MOF_XRGB(255, 255, 255));
	light_.SetDiffuse(MOF_XRGB(220, 220, 220));
	light_.SetSpeculer(MOF_XRGB(255, 255, 255));

	//ゲームの状態初期化
	currentGameState_ = GAME_STATE::NOMAL;


	//タスクの登録
	RegisterTask();

}
void Scene::CBattleScene::Update()
{

	if (currentGameState_ == GAME_STATE::CLEAR || 
		currentGameState_ == GAME_STATE::OVER)
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
	updateTask_.Excution();


	//エフェクト描画更新
	EffectRendererInstance.Update();
	//エフェクト操作更新
	EffectControllerInstance.Update();
	//時間操作更新
	TimeScaleControllerInstance.Update();
	//カメラ操作更新
	CameraControllerInstance.Update(player_->GetPosition(), player_->GetPosition());
	//ショットマネージャー更新
	ShotManagerInstance.Update();

	//ショット削除処理
	ShotManagerInstance.Delete();
	//エフェクト削除処理
	EffectControllerInstance.Delete();
	//アクター削除処理
	ActorObjectManagerInstance.Delete();
	
}

void Scene::CBattleScene::Render()
{
	//描画タスク実行
	renderTask_.Excution();

}

void Scene::CBattleScene::RenderDebug()
{
	//ステージデバッグ描画
	stageManager_.RenderDebug();

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
	CGraphicsUtilities::RenderBox(player_->GetCollider(), Vector4(0, 1, 0, 0.2f));
	//プレイヤー回避時当たり判定デバッグ描画
	if (player_->IsEscape())
	{
		CGraphicsUtilities::RenderBox(player_->GetEscapeCollider(), Vector4(0, 0, 1, 0.2f));
	}
	if (enemyCreateThread_.IsComplete())
	{
		//敵当たり判定デバッグ描画
		enemyManager_.RenderDebug();
	}
}

void Scene::CBattleScene::Render2D()
{
	//２D描画タスク実行
	render2DTask_.Excution();

}

void Scene::CBattleScene::Render2DDebug()
{
	CGraphicsUtilities::RenderString(0, 0, "POS X:%.2f,Z:%.2f", player_->GetPosition().x, player_->GetPosition().z);
	CGraphicsUtilities::RenderString(0, 30, "VEL X:%.2f,Z:%.2f", player_->GetVelocity().x, player_->GetVelocity().z);

	CGraphicsUtilities::RenderString(0, 60, "角度：%.2f", MOF_ToDegree(player_->GetRotate().y));
	CGraphicsUtilities::RenderString(0, 90, player_->IsReverse() ? "向き：左" :"向き：右");

	CGraphicsUtilities::RenderString(400, 0, "タイムスケール：%.2f", TimeScaleControllerInstance.GetTimeScale());
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
	//アクターマネージャー解放
	ActorObjectManagerInstance.Release();
	//アクターID解放
	IDManagerInstance.Release();

	//ステージ解放
	stageManager_.Release();

	//プレイヤー解放
	player_->Release();
	player_.reset();
	ServiceLocator<CPlayer>::Release();
	playerUiRender_.reset();

	//敵解放
	enemyManager_.Release();
	enemySpawner_.reset();

	//HPバー解放
	npcHpRender_.Release();
	
	//リソース解放
	ResourceManager<Effekseer::EffectRef>::GetInstance().Release();
	ResourcePtrManager<CMeshContainer>::GetInstance().Release();
	ResourcePtrManager<CSprite3D>::GetInstance().Release();
	ResourcePtrManager<CTexture>::GetInstance().Release();
	ResourcePtrManager<CFont>::GetInstance().Release();


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

bool Scene::CBattleScene::CreateEnemys()
{
	//配列初期化
	enemyManager_.ClearEnemyArray();
	npcHpRender_.Reset();
	for (auto spawner : *enemySpawner_)
	{
		spawner->Reset();
	}

	//現在の区画から敵の情報を受け取る
	auto division = stageManager_.GetCurrentDivision();
	auto enemysParam = division->GetEnemysParam();
	int enemyCount = division->GetEnemyCount();

	//クリア条件に敵の数を設定
	clearTermProvider_->SetEnemyMaxCount(enemyCount);

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
	clearTermProvider_->SetBossMaxCount(enemyCount);

	//敵のスポナー取得
	auto spawner = division->GetEnemySpawners();
	enemySpawner_ = spawner;
	


	//敵のビルダーの辞書
	EnemyBuilderDictionary dictionary;

	for (int i = 0; i < enemyCount; i++)
	{
		//敵のタイプに合ったビルダーを取得
		auto builder = dictionary.Get(enemysParam->at(i)->GetParam().type_);

		//敵を追加する
		enemyManager_.AddEnemy(builder->Create(enemysParam->at(i)));

		//敵をマネージャーに登録
		ActorObjectManagerInstance.Add(enemyManager_.GetEnemy(i));
		//敵のHPバー生成＆オブザーバに登録
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

	//更新タスク登録
	RegisterUpdateTask();

	//衝突タスク登録
	RegisterCollisionTask();

	//描画タスク登録
	RegisterRenderTask();

	//２D描画タスク登録
	RegisterRender2DTask();

}

void Scene::CBattleScene::RegisterUpdateTask()
{
	////////////////////////////////////////////////
	///		更新タスク
	////////////////////////////////////////////////

	//リトライタスク
	updateTask_.AddTask("RetryTask", TASK_EVENT,
		[&]()
	{
		//リトライ
		if (InputManagerInstance.GetInput(0)->IsPush(INPUT_KEY_RETRY))
		{
			//フェード
			auto sceneEffect = std::make_shared<Scene::SceneChangeFade>(0.5f,0.5f,0.5f);
			//初期化
			SceneInitializeService::GetService()->InitializeScene(sceneEffect);
			return;
		}
		
	}
	);
	//更新タスク
	updateTask_.AddTask("UpdateTask1", TASK_MAIN1,
		[&]()
	{
		
		//タイマー更新
		timer_.Update();

		//プレイヤー更新
		player_->Update();
	}
	);

	//条件の設定タスク
	updateTask_.AddTask("SetConditionTask", TASK_MAIN2,
		[&]()
	{

		//死亡判定
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
	///		当たり判定タスク
	////////////////////////////////////////////////

	updateTask_.AddTask("CollisionTask1", TASK_COLLISION,
		[&]()
	{
		if (currentGameState_ == GAME_STATE::NOMAL)
		{
			//プレイヤーとオブジェクトの当たり判定
			for (size_t i = 0; i < stageManager_.GetCurrentDivision()->GetObjCount(); i++)
			{
				auto obj = stageManager_.GetCurrentDivision()->GetObj(i);
				CCollision::CollisionObj(player_, obj);
			}

			//プレイヤーと弾の当たり判定
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
	///		描画タスク
	////////////////////////////////////////////////

	renderTask_.AddTask("RenderTask1", TASK_MAIN1,
		[&]()
	{
		//ステージ描画
		stageManager_.Render();

		//プレイヤー描画
		player_->Render();

	}
	);
	renderTask_.AddTask("RenderTask2", TASK_MAIN3,
		[&]()
		{
			//ショット描画
			ShotManagerInstance.Render();
			//エフェクト描画
			EffectRendererInstance.Render();
		}
		);
}

void Scene::CBattleScene::RegisterRender2DTask()
{
	////////////////////////////////////////////////
	///		２D描画タスク
	////////////////////////////////////////////////

	render2DTask_.AddTask("Render2DTask1", TASK_MAIN2,
		[&]()
	{
		///プレイヤーのUI描画
		playerUiRender_->Render();

		//リトライ描画
		if (currentGameState_ == GAME_STATE::CLEAR || currentGameState_ == GAME_STATE::OVER)
		{
			CGraphicsUtilities::RenderString(20, 950, "F2でリトライ");
			CGraphicsUtilities::RenderString(20, 1000, "F3でタイトルへ");
		}

		//ゲームクリア描画
		if (currentGameState_ == GAME_STATE::CLEAR)
		{
			CRectangle rect;
			font_.CalculateStringRect(0, 0, "全部倒したあああああ", rect);
			font_.RenderString(g_pGraphics->GetTargetWidth() * 0.5f - (rect.GetWidth() * 0.5f), g_pGraphics->GetTargetHeight() * 0.5f - (rect.GetHeight() * 0.5f), "全部倒したあああああ");
		}
	}
	);

}

void Scene::CBattleScene::RegisterAfterSpawn()
{
	////////////////////////////////////////////////
	///		スポーン時に登録するタスク
	////////////////////////////////////////////////

	updateTask_.AddTask("AfterSpawnUpdate", TASK_MAIN1,
		[&]()
	{
		

		//敵スポナー更新
		for (size_t i = 0; i < enemySpawner_->size(); i++)
		{
			enemySpawner_->at(i)->Update(enemyManager_.GetEnemy(i));
		}
		

		//敵更新
		enemyManager_.Update();

		//ステージクリア判定
		if (stageManager_.IsClear(clearTermProvider_))
		{
			if (currentGameState_ == GAME_STATE::NOMAL)
			{
				player_->ClearPose();
				currentGameState_ = GAME_STATE::CLEAR;
			}
		}
		//ステージの区画をクリアしているなら
		else if (stageManager_.GetCurrentDivision()->IsClear(clearTermProvider_) && 
				 currentGameState_ == GAME_STATE::NOMAL)
		{
			updateTask_.DeleteTask("AfterSpawnUpdate");
			updateTask_.DeleteTask("AfterSpawnCollision");
			renderTask_.DeleteTask("AfterSpawnRender");
			render2DTask_.DeleteTask("AfterSpawnRender2D");

			//次の区画へ
			stageManager_.NextPhase();

			//敵を生成する
			enemyCreateThread_.Create([this]() { return CreateEnemys(); },
										[this]() {RegisterAfterSpawn(); }
										);
			//タイマーをリセット
			timer_.Start();
		}


		//ステージ更新
		stageManager_.Update();
	});

	//敵の衝突判定
	updateTask_.AddTask("AfterSpawnCollision", TASK_COLLISION,
		[&]()
		{
			//敵の当たり判定
			for (size_t i = 0; i < enemyManager_.GetEnemyMaxCount(); i++)
			{
				EnemyPtr enemy = enemyManager_.GetEnemy(i);
				if (!enemy->IsShow())
				{
					continue;
				}
				//敵とプレイヤー
				CCollision::CollisionObj(player_, enemy);

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
				for (size_t j = 0; j < stageManager_.GetCurrentDivision()->GetObjCount(); j++)
				{
					auto obj = stageManager_.GetCurrentDivision()->GetObj(j);
					CCollision::CollisionObj(enemy, obj);
				}
			}
		}
		);

	//敵の描画
	renderTask_.AddTask("AfterSpawnRender", TASK_MAIN1,
		[&]()
	{
		//敵描画
		enemyManager_.Render();
	}
	);

	//敵HP描画
	render2DTask_.AddTask("AfterSpawnRender2D", TASK_MAIN1,
		[&]()
	{
		//HPバー描画
		npcHpRender_.Render();
		//2DHPバー描画
		npcHpRender_.Render2D();
	}
	);
}