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
	///		�X�V�^�X�N
	////////////////////////////////////////////////

	//���g���C�^�X�N
	updateTask_.AddTask("RetryTask", Task::PRIORITY::EVENT,
		[&]()
	{
		//���g���C
		if (InputManagerInstance.GetInput(0)->IsPush(INPUT_KEY_RETRY))
		{
			//�t�F�[�h
			float time = 0.5f;
			auto sceneEffect = std::make_shared<Scene::SceneChangeFade>(time, time, time);
			//������
			SceneInitializeService::GetService()->InitializeScene(sceneEffect);
			return;
		}

	}
	);
	//�X�V�^�X�N
	updateTask_.AddTask("UpdateTask1", Task::PRIORITY::MAIN1,
		[&]()
	{

		//�^�C�}�[�X�V
		timer_.Update();

		//�v���C���[�X�V
		player_->Update();
	}
	);

	//�����̐ݒ�^�X�N
	updateTask_.AddTask("SetConditionTask", Task::PRIORITY::MAIN2,
		[&]()
	{

		//���S����
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
	///		�����蔻��^�X�N
	////////////////////////////////////////////////

	updateTask_.AddTask("CollisionTask1", Task::PRIORITY::COLLISION,
		[&]()
	{
		if (currentGameState_ == GAME_STATE::NOMAL)
		{
			//�v���C���[�ƃI�u�W�F�N�g�̓����蔻��
			for (size_t i = 0; i < stageManager_.GetCurrentDivision()->GetObjCount(); i++)
			{
				auto obj = stageManager_.GetCurrentDivision()->GetObj(i);
				CCollision::CollisionObj(player_, obj);
			}

			//�v���C���[�ƒe�̓����蔻��
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
	///		�`��^�X�N
	////////////////////////////////////////////////

	renderTask_.AddTask("RenderTask1", Task::PRIORITY::MAIN1,
		[&]()
	{
		//�X�e�[�W�`��
		stageManager_.Render();

		//�v���C���[�`��
		player_->Render();

	}
	);
	renderTask_.AddTask("RenderTask2", Task::PRIORITY::MAIN3,
		[&]()
	{
		//�V���b�g�`��
		ShotManagerInstance.Render();
		//�G�t�F�N�g�`��
		EffectRendererInstance.Render();
	}
	);
}

void Scene::CBattleScene::RegisterRender2DTask()
{
	////////////////////////////////////////////////
	///		�QD�`��^�X�N
	////////////////////////////////////////////////

	render2DTask_.AddTask("Render2DTask1", Task::PRIORITY::MAIN2,
		[&]()
	{
		///�v���C���[��UI�`��
		playerUiRender_.Render();

		//���g���C�`��
		if (currentGameState_ == GAME_STATE::CLEAR || currentGameState_ == GAME_STATE::OVER)
		{
			CGraphicsUtilities::RenderString(20, 950, "F2�Ń��g���C");
			CGraphicsUtilities::RenderString(20, 1000, "F3�Ń^�C�g����");
		}

		//�Q�[���N���A�`��
		if (currentGameState_ == GAME_STATE::CLEAR)
		{
			CRectangle rect;
			font_.CalculateStringRect(0, 0, "�S���|��������������", rect);
			font_.RenderString(g_pGraphics->GetTargetWidth() * 0.5f - (rect.GetWidth() * 0.5f), g_pGraphics->GetTargetHeight() * 0.5f - (rect.GetHeight() * 0.5f), "�S���|��������������");
		}
	}
	);

}

void Scene::CBattleScene::RegisterAfterSpawn()
{
	////////////////////////////////////////////////
	///		�X�|�[�����ɓo�^����^�X�N
	////////////////////////////////////////////////

	updateTask_.AddTask("AfterSpawnUpdate", Task::PRIORITY::MAIN1,
		[&]()
	{


		//�G�X�|�i�[�X�V
		for (size_t i = 0; i < enemySpawner_->size(); i++)
		{
			enemySpawner_->at(i)->Update(enemyManager_.GetEnemy(i));
		}


		//�G�X�V
		enemyManager_.Update();

		//�X�e�[�W�N���A����
		if (stageManager_.IsClear(clearTermProvider_))
		{
			if (currentGameState_ == GAME_STATE::NOMAL)
			{
				player_->ClearPose();
				currentGameState_ = GAME_STATE::CLEAR;
			}
		}
		//�X�e�[�W�̋����N���A���Ă���Ȃ�
		else if (stageManager_.GetCurrentDivision()->IsClear(clearTermProvider_) &&
			currentGameState_ == GAME_STATE::NOMAL)
		{
			updateTask_.DeleteTask("AfterSpawnUpdate");
			updateTask_.DeleteTask("AfterSpawnCollision");
			renderTask_.DeleteTask("AfterSpawnRender");
			render2DTask_.DeleteTask("AfterSpawnRender2D");

			//���̋���
			stageManager_.NextPhase();

			//�G�𐶐�����
			enemyCreateThread_.Create([this]() { return CreateEnemys(); },
				[this]() {RegisterAfterSpawn(); }
			);
			//�^�C�}�[�����Z�b�g
			timer_.Start();
		}


		//�X�e�[�W�X�V
		stageManager_.Update();
	});

	//�G�̏Փ˔���
	updateTask_.AddTask("AfterSpawnCollision", Task::PRIORITY::COLLISION,
		[&]()
	{
		//�G�̓����蔻��
		for (size_t i = 0; i < enemyManager_.GetEnemyMaxCount(); i++)
		{
			EnemyPtr enemy = enemyManager_.GetEnemy(i);
			if (!enemy->IsShow())
			{
				continue;
			}
			//�G�ƃv���C���[
			CCollision::CollisionObj(player_, enemy);

			if (!enemy->IsInvincible())
			{
				//�G�ƒe
				for (size_t j = 0; j < ShotManagerInstance.GetShotCount(); j++)
				{
					auto shot = ShotManagerInstance.GetShot(j);
					CCollision::CollisionObj(shot, enemy);
				}
			}

			//�G�ƃI�u�W�F�N�g
			for (size_t j = 0; j < stageManager_.GetCurrentDivision()->GetObjCount(); j++)
			{
				auto obj = stageManager_.GetCurrentDivision()->GetObj(j);
				CCollision::CollisionObj(enemy, obj);
			}
		}
	}
	);

	//�G�̕`��
	renderTask_.AddTask("AfterSpawnRender", Task::PRIORITY::MAIN1,
		[&]()
	{
		//�G�`��
		enemyManager_.Render();
	}
	);

	//�GHP�`��
	render2DTask_.AddTask("AfterSpawnRender2D", Task::PRIORITY::MAIN1,
		[&]()
	{
		//HP�o�[�`��
		npcHpRender_.Render();
		//2DHP�o�[�`��
		npcHpRender_.Render2D();
	}
	);
}