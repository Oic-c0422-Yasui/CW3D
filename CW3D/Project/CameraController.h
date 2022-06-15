#pragma once
#include "Singleton.h"
#include "CameraBase.h"
#include "TimeController.h"



	class CCameraController : public Singleton<CCameraController>
	{
		friend class Singleton<CCameraController>;
	private:

		CameraPtr	m_Camera;
		CameraPtr	m_NextCamera;
		CameraPtr	m_DefaultCamera;
		bool		m_LeapFlg;
		bool		m_EndLeapFlg;
		float		m_EndLeapTime;
		Sample::MyUtilities::EASING_TYPE m_EndEaseType;
		float		m_Time;
		float		m_CurrentTime;
		bool		m_TimerStartFlg;
		
		CCameraController();

	public:
		~CCameraController();

		void Load(const CameraPtr& camera);
		void SetCamera(const CameraPtr& camera);
		void SetCamera(const CameraPtr& camera, float tTime);
		void SetCamera(const CameraPtr& camera, float tTime, Sample::MyUtilities::EASING_TYPE startEaseType, float leapStartTime, Sample::MyUtilities::EASING_TYPE endEaseType, float leapEndTime);
		void SetDefault() { SetCamera(m_DefaultCamera); }
		void Update(Vector3 pos, Vector3 lookPos);

		void Render2DDebug();

		const Vector3& GetPosition() const noexcept
		{
			return m_Camera->GetPos();
		}
		const Vector3& GetLookPosition() const noexcept
		{
			return m_Camera->GetLookPos();
		}

		void SetTargetPos(const Vector3& pos)
		{
			m_Camera->SetPos(pos);
		}
		void SetTargetLookPos(const Vector3& pos)
		{
			m_Camera->SetLookPos(pos);
		}
		void SetTarget(const Vector3& pos, const Vector3& lookPos)
		{
			SetTargetPos(pos);
			SetTargetLookPos(lookPos);
		}

	};

//簡易アクセス用
#define CameraControllerInstance 	CCameraController::GetInstance()

