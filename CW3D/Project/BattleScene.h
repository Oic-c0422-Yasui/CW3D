#pragma once
#include "SceneBase.h"
#include	"Common.h"

#include	"MofInput.h"
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
#include	"CreateThread.h"
#include	"TaskManager.h"

class CBattleScene : public CSceneBase
{
private:
	//�v���C���[
	PlayerPtr m_Player;
	//�G�}�l�[�W���[
	Sample::EnemyManager m_EnemyManager;
	//�G�X�|�i�[
	Spawner::EnemySpawnerArray m_EnemySpawner;
	//�G�����X���b�h
	ThreadCreator m_EnemyCreateThread;
	//�X�V�^�X�N
	Sample::TaskManager	m_UpdateTask;
	//�`��^�X�N
	Sample::TaskManager	m_RenderTask;
	//Render2D�^�X�N
	Sample::TaskManager	m_Render2DTask;



	//���C�g
	CDirectionalLight m_Light;
	//�t�H���g
	CFont m_Font;
	//�GHP�o�[
	std::vector<Sample::EnemyHPRenderPtr> m_EnemysHPRender;
	//�v���C���[UI
	Sample::PlayerUIRenderPtr m_PlayerUIRender;
	//UI�쐬
	Sample::CBattleUICreater m_UICreater;
	//�X�e�[�W�}�l�[�W���[
	Sample::CStageManager m_StageManager;
	//�N���A�����ɕK�v�Ȃ��̂�n���v���o�C�_
	Sample::ClearTermProviderPtr m_ClearTermProvider;

	//�N���A�t���O
	bool m_GameClearFlg;
	//���S�t���O
	bool m_GameOverFlg;

	Sample::CTimer m_Timer;

private:
	//�Փ˔�����܂Ƃ߂��֐�
	void Collision();
	//�G�̐���
	bool CreateEnemys();
	//�^�X�N�̓o�^
	void RegisterTask();
	void RegisterUpdateTask();
	void RegisterCollisionTask();
	void RegisterRenderTask();
	void RegisterRender2DTask();

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
	void Release();
};



