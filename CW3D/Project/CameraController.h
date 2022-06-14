#pragma once
#include "GameDefine.h"
#include "Singleton.h"


class CCameraController : public Singleton<CCameraController>
{
	friend class Singleton<CCameraController>;
private:
	CCamera m_ActionCamera;
	CCamera m_Camera;
	CVector3 m_OffsetPos;
	CVector3 m_OffsetLookPos;
	CVector3 m_LookPos;
	CVector3 m_Position;
	CVector3 m_TargetPosition;
	CVector3 m_TargetLookPos;

	struct CAMERA_STRUCT
	{
		CCamera  Camera;
		CVector3 OffsetPos;
		CVector3 OffsetLookPos;
		CVector3 LookPos;
		CVector3 Position;
		CVector3 TargetPosition;
		CVector3 TargetLookPos;
	};
	CAMERA_STRUCT m_Cameras[2];

	int		 m_CameraType;

	enum CAMERA_TYPE
	{
		CAMERA_NOMAL,
		CAMERA_ACTION,
	};

	CCameraController();
public:
	~CCameraController();
	void Initialize();
	void Update(Vector3 pos,Vector3 lookPos);

	void Render2DDebug();

	Vector3 GetPosition()
	{
		switch (m_CameraType)
		{
		case CAMERA_NOMAL:
		{
			return m_Cameras[CAMERA_NOMAL].Position;
		}
		case CAMERA_ACTION:
		{
			return m_Cameras[CAMERA_ACTION].Position;
		}
		default:
			break;
		}

		return m_Cameras[CAMERA_NOMAL].Position;
	}
	Vector3 GetLookPosition()
	{
		switch (m_CameraType)
		{
		case CAMERA_NOMAL:
		{
			return m_Cameras[CAMERA_NOMAL].LookPos;
		}
		case CAMERA_ACTION:
		{
			return m_Cameras[CAMERA_ACTION].LookPos;
		}
		default:
			break;
		}

		return m_Cameras[CAMERA_NOMAL].LookPos;
	}

};

//簡易アクセス用
#define CameraControllerInstance 	Sample::CCameraController::GetInstance()