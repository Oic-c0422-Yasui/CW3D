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
	//�Q�[���̏��
	enum class GAME_STATE
	{
		NOMAL,	//�Q�[����
		CLEAR,	//�Q�[���N���A
		OVER,	//�Q�[���I�[�o�[
	};

	class CBattleScene : public IScene
	{
	private:
		//�v���C���[
		PlayerPtr player_;
		//�G�}�l�[�W���[
		ActionGame::EnemyManager enemyManager_;
		//�G�X�|�i�[
		Spawner::EnemySpawnerArrayPtr enemySpawner_;
		//�G�����X���b�h
		ThreadCreator enemyCreateThread_;
		//�X�V�^�X�N
		ActionGame::TaskManager	updateTask_;
		//�`��^�X�N
		ActionGame::TaskManager	renderTask_;
		//Render2D�^�X�N
		ActionGame::TaskManager	render2DTask_;

		//���C�g
		CDirectionalLight light_;
		//�t�H���g
		CFont font_;

		//NPC��HP�o�[
		ActionGame::NPCHPRenderManager npcHpRender_;
		//�v���C���[UI
		ActionGame::PlayerUIRenderPtr playerUiRender_;
		//UI�쐬
		ActionGame::BattleUICreater uiCreater_;
		//�X�e�[�W�}�l�[�W���[
		ActionGame::StageManager stageManager_;
		//�N���A�����ɕK�v�Ȃ��̂�n���v���o�C�_
		ActionGame::ClearTermProviderPtr clearTermProvider_;

		//���݂̃Q�[���̏��
		GAME_STATE currentGameState_;

		ActionGame::CTimer timer_;

	private:
		//�G�̐���
		bool CreateEnemys();
		//�^�X�N�̓o�^
		void RegisterTask();
		//�X�V�^�X�N
		void RegisterUpdateTask();
		//�����蔻��^�X�N
		void RegisterCollisionTask();
		//�`��^�X�N
		void RegisterRenderTask();
		//�QD�^�X�N
		void RegisterRender2DTask();
		//�G�X�|�[����^�X�N
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





