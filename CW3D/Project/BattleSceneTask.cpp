#include "BattleScene.h"
#include	"CollisionEnemyEnemy.h"
#include	"CollisionPlayerEnemy.h"
#include	"CollisionShotEnemy.h"
#include	"CollisionShotPlayer.h"
#include	"CollisionObjectPlayer.h"
#include	"CollisionObjectEnemy.h"

using namespace ActionGame;

void Scene::CBattleScene::RegisterUpdateTask()
{
	////////////////////////////////////////////////
	///		更新タスク
	////////////////////////////////////////////////

	//リトライタスク
	updateTask_.AddTask("RetryTask", Task::PRIORITY::EVENT,
		[&]()
	{
		//リトライ
		if (InputManagerInstance.GetInput(0)->IsPush(INPUT_KEY_RETRY))
		{
			//フェード
			float time = 0.5f;
			auto sceneEffect = std::make_shared<Scene::SceneChangeFade>(time, time, time);
			//初期化
			SceneInitializeService::GetService()->InitializeScene(sceneEffect);
			return;
		}

	}
	);
	//更新タスク
	updateTask_.AddTask("UpdateTask1", Task::PRIORITY::MAIN1,
		[&]()
	{

		//タイマー更新
		timer_.Update();

		//プレイヤー更新
		player_->Update();
	}
	);

	//条件の設定タスク
	updateTask_.AddTask("SetConditionTask", Task::PRIORITY::MAIN2,
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

	updateTask_.AddTask("CollisionTask1", Task::PRIORITY::COLLISION,
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

	renderTask_.AddTask("RenderTask1", Task::PRIORITY::MAIN1,
		[&]()
	{
		//ステージ描画
		stageManager_.Render();

		//プレイヤー描画
		player_->Render();

	}
	);
	renderTask_.AddTask("RenderTask2", Task::PRIORITY::MAIN3,
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

	render2DTask_.AddTask("Render2DTask1", Task::PRIORITY::MAIN2,
		[&]()
	{
		///プレイヤーのUI描画
		playerUiRender_.Render();

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

	updateTask_.AddTask("AfterSpawnUpdate", Task::PRIORITY::MAIN1,
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
	updateTask_.AddTask("AfterSpawnCollision", Task::PRIORITY::COLLISION,
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
				for (size_t j = 0; j < ShotManagerInstance.GetShotCount(); j++)
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
	renderTask_.AddTask("AfterSpawnRender", Task::PRIORITY::MAIN1,
		[&]()
	{
		//敵描画
		enemyManager_.Render();
	}
	);

	//敵HP描画
	render2DTask_.AddTask("AfterSpawnRender2D", Task::PRIORITY::MAIN1,
		[&]()
	{
		//HPバー描画
		npcHpRender_.Render();
		//2DHPバー描画
		npcHpRender_.Render2D();
	}
	);
}