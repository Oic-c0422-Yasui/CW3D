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

#include	"BattleUILoader.h"
#include	"EffectLoader.h"

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
#include	"GiveTextureToMaterial.h"

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
		ActionGame::PlayerPtr player_;
		//敵マネージャー
		ActionGame::CEnemyManager enemyManager_;
		//敵スポナー
		Spawner::EnemySpawnerArrayPtr enemySpawner_;
		//敵生成スレッド
		ThreadCreator enemyCreateThread_;
		//更新タスク
		Task::CTaskManager	updateTask_;
		//描画タスク
		Task::CTaskManager	renderTask_;
		//2D描画タスク
		Task::CTaskManager	render2DTask_;

		//ライト
		CDirectionalLight light_;
		//フォント
		CFont font_;

		//NPCのHPバー
		ActionGame::CNPCHPRenderManager npcHpRender_;
		//プレイヤーUI
		ActionGame::CPlayerUIRender playerUiRender_;
		//ステージマネージャー
		ActionGame::StageManager stageManager_;
		//クリア条件に必要なものを渡すプロバイダ
		ClearTerm::ProviderPtr clearTermProvider_;

		//現在のゲームの状態
		GAME_STATE currentGameState_;

		//タイマー
		ActionGame::CTimer timer_;

		//ノーマルマップシェーダー
		MyClass::NormalMapParameterPtr normalMap_;

		MyClass::CGiveTextureToMaterial giveTexture_;

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





