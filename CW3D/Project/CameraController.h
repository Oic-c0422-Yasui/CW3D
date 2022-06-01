#pragma once
#include "GameDefine.h"


class CCameraController
{
private:
	CCamera m_Camera;
	CVector3 m_OffsetPos;
	CVector3 m_OffsetLookPos;
	CVector3 m_LookPos;
	CVector3 m_Position;

public:
	CCameraController();
	~CCameraController();
	void Initialize();
	void Update(Vector3 pos,Vector3 lookPos);

	void Render2DDebug();

	Vector3 GetPosition()
	{
		return m_Position;
	}
	Vector3 GetLookPosition()
	{
		return m_LookPos;
	}

};

