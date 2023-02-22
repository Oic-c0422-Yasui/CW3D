#pragma once
#include "IScene.h"
#include	"Common.h"

#include	"ResourceManager.h"
#include	"GameDefine.h"
#include	"CameraController.h"

#include	"Player.h"
#include	"Enemy.h"
#include	"ShotManager.h"
#include	"EffectController.h"
#include	"EffectRenderer.h"
#include	"IDManager.h"
#include	"TimeScaleController.h"

#include	"EnemyHPRender.h"

#include	"BattleUICreater.h"

#include	"Collision.h"
#include	"PlayerUIRender.h"
#include	"StageManager.h"

#include	"ClearTermProvider.h"

#include	"Timer.h"

#include	"EnemyManager.h"

#include	"EnemySpawner.h"
#include	"EnemySpawnConditionCountLimit.h"
#include	"SpawnCycleFixedRange.h"
#include	"EnemySpawnParameter.h"
#include	"ThreadCreator.h"
#include	"TaskManager.h"
#include	"SceneInitializer.h"
#include	"SceneChangeFade.h"
#include	"SceneChanger.h"

#include	"NPCHPRenderManager.h"


namespace Scene
{
	//ゲームの状態
	enum class GAME_STATE
	{
		NOMAL,	//ゲーム中
		CLEAR,	//ゲームクリア
		OVER,	//ゲームオーバー
	};

	class CBattleScene : public IScene
	{
	private:
		//プレイヤー
		PlayerPtr player_;
		//敵マネージャー
		ActionGame::EnemyManager enemyManager_;
		//敵スポナー
		Spawner::EnemySpawnerArrayPtr enemySpawner_;
		//敵生成スレッド
		ThreadCreator enemyCreateThread_;
		//更新タスク
		ActionGame::TaskManager	updateTask_;
		//描画タスク
		ActionGame::TaskManager	renderTask_;
		//Render2Dタスク
		ActionGame::TaskManager	render2DTask_;

		//ライト
		CDirectionalLight light_;
		//フォント
		CFont font_;

		//NPCのHPバー
		ActionGame::NPCHPRenderManager npcHpRender_;
		//プレイヤーUI
		ActionGame::PlayerUIRenderPtr playerUiRender_;
		//UI作成
		ActionGame::BattleUICreater uiCreater_;
		//ステージマネージャー
		ActionGame::StageManager stageManager_;
		//クリア条件に必要なものを渡すプロバイダ
		ActionGame::ClearTermProviderPtr clearTermProvider_;

		//現在のゲームの状態
		GAME_STATE currentGameState_;

		ActionGame::CTimer timer_;

	private:
		//敵の生成
		bool CreateEnemys();
		//タスクの登録
		void RegisterTask();
		//更新タスク
		void RegisterUpdateTask();
		//当たり判定タスク
		void RegisterCollisionTask();
		//描画タスク
		void RegisterRenderTask();
		//２Dタスク
		void RegisterRender2DTask();
		//敵スポーン後タスク
		void RegisterAfterSpawn();

	public:
		CBattleScene();
		~CBattleScene();
		bool Load() override;
		void Initialize() override;
		void Update() override;
		void Render() override;
		void RenderDebug() override;
		void Render2D() override;
		void Render2DDebug() override;
		void Release() override;
	};
}





