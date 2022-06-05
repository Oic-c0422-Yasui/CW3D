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
#include	"SkillCreater.h"
#include	"IDManager.h"

#include	"EnemyHPRender.h"

#include	"Collision.h"

class CBattleScene : public CSceneBase
{
private:
	CPlayer m_Player;

	std::vector<CEnemy*> m_Enemys;


	CCameraController m_Camera;

	CMeshContainer	m_PlayerMesh;

	CDirectionalLight m_Light;

	CMeshContainer	m_Stage;

	CFont m_Font;

	std::vector<Sample::EnemyHPRender> m_EnemysHPRender;


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

