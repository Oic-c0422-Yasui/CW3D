#pragma once
#include "SceneBase.h"
class CBattleScene : public CSceneBase
{
private:

public:
	CBattleScene();
	~CBattleScene();
	bool Load();
	void Initialize();
	void Update();
	void Render();
	void Release();

};

