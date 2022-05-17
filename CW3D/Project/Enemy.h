#pragma once
#include "GameDefine.h"

class CEnemy
{
private:

public:
	CEnemy();
	~CEnemy();
	bool Load();
	void Initialize();
	void Update();
	void Render();
	void RenderDebug();
	void Release();

};

