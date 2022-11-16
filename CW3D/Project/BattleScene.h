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



class CBattleScene : public CSceneBase
{
private:
	//プレイヤー
	PlayerPtr m_Player;
	//敵マネージャー
	Sample::EnemyManager m_EnemyManager;

	//ライト
	CDirectionalLight m_Light;
	//フォント
	CFont m_Font;
	//敵HPバー
	std::vector<Sample::EnemyHPRenderPtr> m_EnemysHPRender;
	//プレイヤーUI
	Sample::PlayerUIRenderPtr m_PlayerUIRender;
	//UI作成
	Sample::CBattleUICreater m_UICreater;
	//ステージマネージャー
	Sample::CStageManager m_StageManager;
	//クリア条件に必要なものを渡すプロバイダ
	Sample::ClearTermProviderPtr m_ClearTermProvider;

	//クリアフラグ
	bool m_GameClearFlg;
	//死亡フラグ
	bool m_GameOverFlg;

	Sample::CTimer m_Timer;

private:
	//衝突判定をまとめた関数
	void Collision();
	//敵の生成
	void CreateEnemys();
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



