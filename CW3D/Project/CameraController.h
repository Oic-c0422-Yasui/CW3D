#pragma once
#include "GameDefine.h"


class CCameraController
{
private:
	CCamera m_Camera;
	CVector3 m_OffsetPos;
	CVector3 m_OffsetLookPos;

public:
	CCameraController();
	~CCameraController();
	void Initialize();
	void Update(Vector3 pos,Vector3 lookPos);

};

