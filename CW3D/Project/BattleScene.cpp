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
	//インプット読み込み
	auto input = InputManagerInstance.AddInput<ActionGame::MofInput>();
	InputManagerInstance.AddInput<ActionGame::StateInput>();

	//キーボード
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
	//パッド
	input->AddJoyStickHorizontal(INPUT_KEY_HORIZONTAL, 0);
	input->AddJoyStickVertical(INPUT_KEY_VERTICAL, 0);
	input->AddJoypadKey(INPUT_KEY_ATTACK, 0,0);


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


	//カメラ初期化
	CameraPtr camera = std::make_shared<CNomalCamera>(m_Player->GetPosition(), m_Player->GetPosition(),Vector3(0,0,0), Vector3(0, 0, 0));
	CameraControllerInstance.Load(camera);

	//プレイヤーをマネージャーに登録
	ActorObjectManagerInstance.Add(m_Player);
	
	//フォント作成
	m_Font.Create(225, "ＭＳ ゴシック");

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

	//クリア条件のプロバイダーにオブザーバーを登録
	m_ClearTermProvider = std::make_shared<ClearTermProvider>();
	auto& provider = m_ClearTermProvider;
	m_EnemyManager.GetEnemyCountSubject().Subscribe([provider](size_t count) {provider->SetEnemyCount(count); });
	
	//敵生成
	m_EnemyCreateThread.Create([this]() { return CreateEnemys(); },
								[this]() {RegisterAfterSpawn(); }
								);


	m_Timer.GetTimeSubject().Subscribe([provider](float time) { provider->SetDivisionTime(time); });
	
	//ライト設定
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

	//タスクの登録
	RegisterTask();

}

void CBattleScene::Update()
{
	//入力更新
	InputManagerInstance.Update();

	//更新タスク実行
	m_UpdateTask.Excution();


	//エフェクトマネージャー更新
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
	ServiceLocator<CPlayer>::GetInstance().Release();
	m_PlayerUIRender.reset();

	//敵解放
	m_EnemyManager.Release();
	m_EnemySpawner.clear();
	for (int i = 0; i < m_EnemysHPRender.size(); i++)
	{
		m_EnemysHPRender[i].reset();
	}
	m_EnemysHPRender.clear();
	
	//リソース解放
	ActionGame::ResourceManager<Effekseer::EffectRef>::GetInstance().Release();
	ActionGame::ResourcePtrManager<CMeshContainer>::GetInstance().Release();
	ActionGame::ResourcePtrManager<CSprite3D>::GetInstance().Release();
	ActionGame::ResourcePtrManager<CTexture>::GetInstance().Release();
	ActionGame::ResourcePtrManager<CFont>::GetInstance().Release();

	//インプット解放(仮)
	InputManagerInstance.Release();

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

void CBattleScene::Collision()
{
	//if (m_EnemyCreateThread.IsComplete())
	//{
	//	//敵の当たり判定
	//	for (size_t i = 0; i < m_EnemyManager.GetMaxEnemyCount(); i++)
	//	{
	//		EnemyPtr enemy = m_EnemyManager.GetEnemy(i);
	//		if (!enemy->IsShow())
	//		{
	//			continue;
	//		}
	//		//敵とプレイヤー
	//		CCollision::CollisionObj(m_Player, enemy);

	//		if (!enemy->IsInvincible())
	//		{
	//			//for (int j = i + 1; j < m_Enemys.size(); j++)
	//			//{
	//			//	//敵と敵
	//			//	CCollision::CollisionObj(m_Enemys[i], m_Enemys[j]);
	//			//}
	//			//敵と弾
	//			for (int j = 0; j < ShotManagerInstance.GetShotCount(); j++)
	//			{
	//				auto shot = ShotManagerInstance.GetShot(j);
	//				CCollision::CollisionObj(shot, enemy);
	//			}
	//		}

	//		//敵とオブジェクト
	//		for (size_t j = 0; j < m_StageManager.GetCurrentDivision()->GetObjCount(); j++)
	//		{
	//			auto obj = m_StageManager.GetCurrentDivision()->GetObj(j);
	//			CCollision::CollisionObj(enemy, obj);
	//		}
	//	}
	//}
	////プレイヤーとオブジェクトの当たり判定
	//for (size_t i = 0; i < m_StageManager.GetCurrentDivision()->GetObjCount(); i++)
	//{
	//	auto obj = m_StageManager.GetCurrentDivision()->GetObj(i);
	//	CCollision::CollisionObj(m_Player, obj);
	//}

	////プレイヤーと弾の当たり判定
	//for (size_t i = 0; i < ShotManagerInstance.GetShotCount(); i++)
	//{
	//	auto shot = ShotManagerInstance.GetShot(i);
	//	CCollision::CollisionObj(shot, m_Player);
	//}

	//
}

bool CBattleScene::CreateEnemys()
{
	//配列初期化
	m_EnemyManager.ClearEnemyArray();
	m_EnemysHPRender.clear();
	m_EnemySpawner.clear();

	//現在の区画から敵の情報を受け取る
	auto division = m_StageManager.GetCurrentDivision();
	auto enemysParam = division->GetEnemysParam();
	int enemyCount = division->GetEnemyCount();

	//敵の数を設定
	m_ClearTermProvider->SetEnemyMaxCount(enemyCount);

	//敵のビルダーの辞書
	EnemyBuilderDictionary dictionary;

	//スポーン条件
	Spawner::EnemySpawnConditionCountLimitPtr spawnCondition = std::make_shared<Spawner::EnemySpawnConditionCountLimit>(enemyCount);
	m_EnemyManager.GetEnemyCountSubject().Subscribe([spawnCondition](size_t count) {spawnCondition->SetCount(count); });

	//敵スポナーの作成
	/*m_EnemySpawner.push_back(std::make_shared<Spawner::EnemySpawner>(
		Spawner::SpawnConditionArray{ spawnCondition },
		std::make_shared<Spawner::SpawnCycleFixedRange>(10),
		std::make_shared<Spawner::EnemySpawnParameter>(enemysParam),
		m_EnemyManager.));*/

	for (int i = 0; i < enemyCount; i++)
	{
		//敵のタイプに合ったビルダーを取得
		auto builder = dictionary.Get(enemysParam->at(i)->GetParam().m_Type);

		//敵を追加する
		m_EnemyManager.AddEnemy(builder->Create(enemysParam->at(i)));

		//敵をマネージャーに登録
		ActorObjectManagerInstance.Add(m_EnemyManager.GetEnemy(i));
		//敵のHPバー生成＆オブザーバに登録
		m_EnemysHPRender.push_back(std::make_shared<CEnemyHPRender>());
		CHPPresenter::Present(m_EnemyManager.GetEnemy(i), m_EnemysHPRender[i]);
		m_EnemysHPRender[i]->Initialize();
	}

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

		if (m_GameClearFlg || m_GameOverFlg)
		{
			//ゲームオーバーORクリア時、リトライ可能
			if (InputManagerInstance.GetInput(0)->IsPush(INPUT_KEY_RETRY))
			{
				Initialize();
				return;
			}
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

		//クリア判定
		if (m_StageManager.IsClear())
		{
			if (!m_GameClearFlg)
			{
				m_Player->SetClearPose();
				m_GameClearFlg = true;
			}
		}

		//死亡判定
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
	///		衝突タスク
	////////////////////////////////////////////////

	m_UpdateTask.AddTask("CollisionTask1", TASK_COLLISION,
		[&]()
	{
		if (!m_GameClearFlg && !m_GameOverFlg)
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
		if (m_GameClearFlg || m_GameOverFlg)
		{
			CGraphicsUtilities::RenderString(20, 1000, "F2でリトライ");
		}

		//ゲームクリア描画
		if (m_GameClearFlg)
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
	/*
	* スポーン時に登録するタスク
	*/

	m_UpdateTask.AddTask("AfterSpawnUpdate", TASK_MAIN1,
		[&]()
	{
		//敵スポナー更新
		for (auto spawner : m_EnemySpawner)
		{
			spawner.Update(m_EnemyManager);
		}

		//敵更新
		m_EnemyManager.Update();
		//ステージの区画をクリアしているなら
		if (m_StageManager.GetCurrentDivision()->IsClear() && !m_GameClearFlg)
		{
			m_UpdateTask.DeleteTask("AfterSpawnCollision");
			m_UpdateTask.DeleteTask("AfterSpawnUpdate");
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
		m_StageManager.Update(m_ClearTermProvider);
	});

	//敵の衝突判定
	m_UpdateTask.AddTask("AfterSpawnCollision", TASK_COLLISION,
		[&]()
		{
			//敵の当たり判定
			for (size_t i = 0; i < m_EnemyManager.GetMaxEnemyCount(); i++)
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
					//for (int j = i + 1; j < m_Enemys.size(); j++)
					//{
					//	//敵と敵
					//	CCollision::CollisionObj(m_Enemys[i], m_Enemys[j]);
					//}
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
		//敵HPバーの描画入れ替え
		std::sort(m_EnemysHPRender.begin(), m_EnemysHPRender.end(),
			[](ActionGame::EnemyHPRenderPtr& obj1, ActionGame::EnemyHPRenderPtr& obj2)
		{
			return obj1->GetViewPosition().z > obj2->GetViewPosition().z;
		});

		//敵のHPバー描画
		for (auto& enemyHP : m_EnemysHPRender)
		{
			enemyHP->Render();
		}
	}
	);
}