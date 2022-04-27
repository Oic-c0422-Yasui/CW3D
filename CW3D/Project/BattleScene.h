#pragma once
#include "SceneBase.h"

#include "MofInput.h"
#include "ResourceManager.h"
#include "GameDefine.h"
#include "CameraController.h"

#include	"Player.h"

class CBattleScene : public CSceneBase
{
private:
	CPlayer m_Player;
	CCameraController m_Camera;

	CMeshContainer	m_PlayerMesh;

	CDirectionalLight m_Light;

public:
	CBattleScene();
	~CBattleScene();
	bool Load();
	void Initialize();
	void Update();
	void Render();
	void Release();

	

};

