#pragma once
#include "Singleton.h"
#include "CameraBase.h"


namespace Sample
{

	class CCameraController : public Singleton<CCameraController>
	{
		friend class Singleton<CCameraController>;
	private:

		CameraPtr	m_Camera;
		CameraPtr	m_NextCamera;
		CameraPtr	m_DefaultCamera;
		bool		m_LeapFlg;
		bool		m_LeapStartFlg;
		float		m_LeapTime;
		bool		m_LeapEndFlg;
		float		m_TempLeapEndTime;
		Sample::MyUtilities::EASING_TYPE m_EndEaseType;
		float		m_Time;
		float		m_CurrentTime;
		bool		m_TimerStartFlg;

		float		m_QuakePower;
		float		m_QuakeFrequent;
		float		m_QuakeTime;
		float		m_QuakeCurrentTime;

		Vector3		m_TargetPos;
		Vector3		m_TargetLookPos;
		
		CCameraController();
		void Reset();

	public:
		~CCameraController();

		void Load(const CameraPtr& camera);
		void SetCamera(const CameraPtr& camera);
		void SetCamera(const CameraPtr& camera, float tTime);
		void SetCamera(const CameraPtr& camera, float tTime, Sample::MyUtilities::EASING_TYPE startEaseType, float leapStartTime, Sample::MyUtilities::EASING_TYPE endEaseType, float leapEndTime);
		void SetDefault();
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
		const CCamera& GetCamera()
		{
			return m_Camera->GetCamera();
		}

		void Quake(float power, float freq, float time);
		void Enable(const Vector3& pos, const Vector3& lookPos);

	};

}


//簡易アクセス用
#define CameraControllerInstance 	Sample::CCameraController::GetInstance()

