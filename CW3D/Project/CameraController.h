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
		MyUtilities::EASING_TYPE m_EndEaseType;
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
		
		/*
		* @brief	読み込み
		* @param	camera	デフォルトになるカメラ
		*/
		void Load(const CameraPtr& defaultCamera);
		/*
		* @brief	カメラ設定
		* @param	camera	使用するカメラ
		*/
		void SetCamera(const CameraPtr& camera);
		/*
		* @brief	カメラ設定
		* @param	camera	使用するカメラ
		* @param	tTime	カメラを映す時間
		*/
		void SetCamera(const CameraPtr& camera, float tTime);

		/*
		* @brief	カメラ設定(現在のカメラ→使用するカメラ へ移動する際に、補間アニメーションを行う）
		* @param	camera			使用するカメラ
		* @param	tTime			カメラを映す時間
		* @param	startEaseType	遷移開始時のイージングタイプ
		* @param	leapStartTime	遷移開始にかかる時間
		* @param	endEaseType		デフォルトのカメラへ戻る時のイージングタイプ
		* @param	leapEndTime		デフォルトのカメラへ戻るのにかかる時間
		*/
		void SetCamera(const CameraPtr& camera, float tTime, MyUtilities::EASING_TYPE startEaseType, float leapStartTime, MyUtilities::EASING_TYPE endEaseType, float leapEndTime);
		
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

		void SetTargetPos(const Vector3& pos) noexcept
		{
			m_Camera->SetPos(pos);
		}
		void SetTargetLookPos(const Vector3& pos) noexcept
		{
			m_Camera->SetLookPos(pos);
		}
		void SetTarget(const Vector3& pos, const Vector3& lookPos) noexcept
		{
			SetTargetPos(pos);
			SetTargetLookPos(lookPos);
		}
		const CCamera& GetCamera() const noexcept
		{
			return m_Camera->GetCamera();
		}

		void Quake(float power, float freq, float time);
		void Enable(const Vector3& pos, const Vector3& lookPos);

	};

}


//簡易アクセス用
#define CameraControllerInstance 	Sample::CCameraController::GetInstance()

