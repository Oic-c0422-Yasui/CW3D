#pragma once
#include "SceneBase.h"

#include "MofInput.h"
#include "ResourceManager.h"
#include "GameDefine.h"
#include "CameraController.h"

#include	"Player.h"
#include	"EnemyBuilder.h"
#include	"ShotManager.h"
#include	"EffectController.h"
#include	"IDManager.h"
#include	"TimeController.h"

#include	"EnemyHPRender.h"

#include	"BattleUICreater.h"

#include	"Collision.h"
#include	"PlayerUIRender.h"
#include	"StageManager.h"

class CBattleScene : public CSceneBase
{
private:
	PlayerPtr m_Player;

	std::vector<Sample::EnemyPtr> m_Enemys;

	CDirectionalLight m_Light;

	CFont m_Font;

	std::vector<Sample::EnemyHPRenderPtr> m_EnemysHPRender;
	Sample::PlayerUIRenderPtr m_PlayerUIRender;

	Sample::CBattleUICreater m_UICreater;

	Sample::CStageManager m_StageManager;

	bool m_GameClearFlg;
	bool m_GameOverFlg;

private:
	void Collision();
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



