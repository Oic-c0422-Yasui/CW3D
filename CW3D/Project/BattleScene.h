#pragma once
#include "SceneBase.h"

#include "MofInput.h"
#include "ResourceManager.h"
#include "GameDefine.h"
#include "CameraController.h"

#include	"Player.h"
#include	"EnemyBuilder.h"
#include	"ShotManager.h"

class CBattleScene : public CSceneBase
{
private:
	CPlayer m_Player;

	std::vector<CEnemy*> m_Enemys;


	CCameraController m_Camera;

	CMeshContainer	m_PlayerMesh;

	CDirectionalLight m_Light;

	CMeshContainer	m_Stage;

public:
	CBattleScene();
	~CBattleScene();
	bool Load();
	void Initialize();
	void Update();
	void Render();
	void RenderDebug();
	void Release();

	

};

