#pragma once
#include "SceneBase.h"
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

namespace ActionGame
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
		PlayerPtr m_Player;
		//敵マネージャー
		ActionGame::EnemyManager m_EnemyManager;
		//敵スポナー
		Spawner::EnemySpawnerArrayPtr m_EnemySpawner;
		//敵生成スレッド
		ThreadCreator m_EnemyCreateThread;
		//更新タスク
		ActionGame::TaskManager	m_UpdateTask;
		//描画タスク
		ActionGame::TaskManager	m_RenderTask;
		//Render2Dタスク
		ActionGame::TaskManager	m_Render2DTask;

		//ライト
		CDirectionalLight m_Light;
		//フォント
		CFont m_Font;

		//NPCのHPバー
		ActionGame::NPCHPRenderManager m_NPCHPRender;
		//プレイヤーUI
		ActionGame::PlayerUIRenderPtr m_PlayerUIRender;
		//UI作成
		ActionGame::CBattleUICreater m_UICreater;
		//ステージマネージャー
		ActionGame::CStageManager m_StageManager;
		//クリア条件に必要なものを渡すプロバイダ
		ActionGame::ClearTermProviderPtr m_ClearTermProvider;

		//現在のゲームの状態
		GAME_STATE m_CurrentGameState;

		ActionGame::CTimer m_Timer;

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




