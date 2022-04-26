#pragma once
#include "GameDefine.h"


class CCameraController
{
private:
	CCamera m_Camera;

public:
	CCameraController();
	~CCameraController();
	void Initialize();
	void Update(Vector3 pos,Vector3 lookPos);

};

