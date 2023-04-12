#include "BattleScene.h"
#include "HPPresenter.h"
#include "SkillPresenter.h"
#include "NormalCamera.h"
#include "ActorObjectManager.h"
#include "Stage1.h"
#include "JsonStageLoader.h"	


using namespace ActionGame;

Scene::CBattleScene::CBattleScene()
	: player_(std::make_shared<CPlayer>())
	, enemyManager_()
	, enemySpawner_(std::make_shared<Spawner::EnemySpawnerArray>())
	, currentGameState_(GAME_STATE::NOMAL)
	, playerUiRender_()
	, normalMap_(std::make_shared<MyClass::CNormalMapParameter>())
	, normalMapSkin_(std::make_shared<MyClass::CNormalMapSkinnedParameter>())
	, giveTexture_(std::make_shared<MyClass::CGiveTextureToMaterial>())
{
}

Scene::CBattleScene::~CBattleScene()
{
}

bool Scene::CBattleScene::Load()
{
	if (!giveTexture_->Load())
	{
		return false;
	}
	CServiceLocator<MyClass::CGiveTextureToMaterial>::SetService(giveTexture_);

	//メッシュ読み込み
	auto tempMesh = std::make_shared<CMeshContainer>();
	if (tempMesh->Load("Mesh/player.mom") != MOFMODEL_RESULT_SUCCEEDED)
	{
		return false;
	}
	ResourcePtrManager<CMeshContainer>::GetInstance().AddResource("Player", "Player", tempMesh);
	//giveTexture_->Give(tempMesh);

	tempMesh = std::make_shared<CMeshContainer>();
	if (tempMesh->Load("Mesh/Shadow/Shadow.mom") != MOFMODEL_RESULT_SUCCEEDED)
	{
		return false;
	}
	ResourcePtrManager<CMeshContainer>::GetInstance().AddResource("Chara", "Shadow", tempMesh);
	giveTexture_->Give(tempMesh);

	//UIテクスチャ読み込み
	if (!ActionGame::CBattleUILoader::Load())
	{
		return false;
	}

	//シェーダー読み込み
	normalMap_ = std::make_shared<MyClass::CNormalMapParameter>();
	if (!normalMap_->Load("Shader/NormalMap.hlsl"))
	{
		return false;
	}
	ResourcePtrManager<MyClass::CNormalMapParameter>::GetInstance().AddResource("Shader","NormalMap", normalMap_);
	normalMapSkin_ = std::make_shared<MyClass::CNormalMapSkinnedParameter>();
	if (!normalMapSkin_->Load("Shader/NormalMapSkin.hlsl"))
	{
		return false;
	}
	ResourcePtrManager<MyClass::CNormalMapSkinnedParameter>::GetInstance().AddResource("Shader", "NormalMapSkin", normalMapSkin_);

	//プレイヤー読み込み
	auto input = InputManagerInstance.GetInput(0);
	player_->SetInput(input);
	if (!player_->Load())
	{
		return false;
	}
	//サービスロケーターの設定
	CServiceLocator<CPlayer>::SetService(player_);

	//プレイヤーUI読み込み
	if (!playerUiRender_.Load(player_))
	{
		return false;
	}

	//カメラ読み込み
	auto camera = std::make_shared<CNormalCamera>(
		player_->GetPosition(), player_->GetPosition(),Vector3(0,0,0), Vector3(0, 0, 0));
	CameraControllerInstance.Load(camera);
	


	//エフェクト読み込み
	EffectRendererInstance.SetUp();
	if (!ActionGame::EffectLoader::Load())
	{
		return false;
	}

	//ステージ情報読み込み
	JsonStageLoader stageLoader;
	if (!stageLoader.Load("Data/Stage1.json"))
	{
		return false;
	}
	
	//ステージ読み込み
	auto stage = std::make_shared<CStage1>();
	stageManager_.Load(stage, stageLoader.GetDivisionArray());

	//プレイヤーをマネージャーに登録
	ActorObjectManagerInstance.Add(player_);

	//UI非表示のメッセージ登録
	npcHpRender_.RegistSendMessage();
	
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
	playerUiRender_.Initialize();

	//クリア条件のプロバイダーにオブザーバーを登録
	clearTermProvider_ = std::make_shared<ClearTerm::CProvider>();
	auto& provider = clearTermProvider_;
	enemyManager_.GetEnemyCountSubject().Subscribe([provider](size_t count) {provider->SetEnemyCount(count); });
	enemyManager_.GetBossCountSubject().Subscribe([provider](size_t count) {provider->SetBossCount(count); });
	timer_.GetTimeSubject().Subscribe([provider](float time) { provider->SetDivisionTime(time); });
	
	//敵生成スレッド作成
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
		//フェードエフェクト
		const float time = 0.5f;
		auto sceneEffect = std::make_shared<Scene::SceneChangeFade>(time, time, time);
		//遷移
		if (InputManagerInstance.GetInput(0)->IsPush(INPUT_KEY_BACK))
		{
			//タイトルへ遷移
			SceneChangeService::GetService()->ChangeScene(SCENENO::TITLE, sceneEffect);
			return;
		}
		//リトライ
		if (InputManagerInstance.GetInput(0)->IsPush(INPUT_KEY_RETRY))
		{
			//初期化
			SceneInitializeService::GetService()->InitializeScene(sceneEffect);
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
	//シェーダーにカメラ情報設定
	normalMap_->SetCamera();
	normalMapSkin_->SetCamera();

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

	CGraphicsUtilities::RenderString(400, 0, "タイムスケール：%.2f", TimeScaleControllerInstance.GetTimeScale(CHARA_TYPE::ENEMY));
	Vector2 pos;
	g_pInput->GetMousePos(pos);
	CGraphicsUtilities::RenderString(400, 30, "X:%.1f Y:%.1f", pos.x, pos.y);

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
	CServiceLocator<CPlayer>::Release();
	playerUiRender_.Release();

	//敵解放
	enemyManager_.Release();
	enemySpawner_.reset();


	//HPバー解放
	npcHpRender_.Release();

	//シェーダー解放
	normalMap_.reset();
	normalMapSkin_.reset();
	
	giveTexture_.reset();
	CServiceLocator<MyClass::CGiveTextureToMaterial>::Release();

	//リソース解放
	ResourceManager<Effekseer::EffectRef>::GetInstance().Release();
	ResourcePtrManager<CMeshContainer>::GetInstance().Release();
	ResourcePtrManager<CSprite3D>::GetInstance().Release();
	ResourcePtrManager<CTexture>::GetInstance().Release();
	ResourcePtrManager<CFont>::GetInstance().Release();
	ResourcePtrManager<MyClass::CNormalMapParameter>::GetInstance().Release();
	ResourcePtrManager<MyClass::CNormalMapSkinnedParameter>::GetInstance().Release();


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
	size_t enemyCount = division->GetEnemyCount();

	//クリア条件に敵の数を設定
	clearTermProvider_->SetEnemyMaxCount(enemyCount);

	//ボス数取得
	size_t bossCount = 0;
	for (auto param : *enemysParam)
	{
		if (param->GetParam().isBoss_)
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

	for (size_t i = 0; i < enemyCount; i++)
	{
		//敵のタイプに合ったビルダーを取得
		auto builder = dictionary.Get(enemysParam->at(i)->GetParam().type_);

		//敵を追加する
		enemyManager_.AddEnemy(builder->Create(enemysParam->at(i)));

		//敵をマネージャーに登録
		ActorObjectManagerInstance.Add(enemyManager_.GetEnemy(i));
		//敵のHPバー生成＆オブザーバに登録
		if (enemysParam->at(i)->GetParam().isBoss_)
		{
			auto bossHP = std::make_shared<CBossHPRender>();
			CHPPresenter::Present(enemyManager_.GetEnemy(i), bossHP);
			npcHpRender_.Add(bossHP);
		}
		else
		{
			auto normalHP = std::make_shared<CNormalEnemyHPRender>();
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
	//※BattleSceneTask.cppに処理を記載

	//更新タスク登録
	RegisterUpdateTask();

	//衝突タスク登録
	RegisterCollisionTask();

	//描画タスク登録
	RegisterRenderTask();

	//２D描画タスク登録
	RegisterRender2DTask();

}

