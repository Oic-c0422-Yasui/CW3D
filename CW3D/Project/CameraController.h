#pragma once
#include "Singleton.h"
#include "CameraBase.h"


namespace ActionGame
{

	class CameraController : public Singleton<CameraController>
	{
		friend class Singleton<CameraController>;
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
		
		CameraController();
		void Reset();

	public:
		~CameraController();
		
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
		/*
		* @brief	カメラをデフォルトにする
		*/
		void SetDefault();
		/*
		* @brief	更新
		* @param pos	座標
		* @param lookPos	注視座標 
		*/
		void Update(const Vector3& pos, const Vector3& lookPos);

		/*
		* @brief	２Dデバッグ描画
		*/
		void Render2DDebug();

		/*
		* @brief	座標取得
		* @return	座標
		*/
		const Vector3& GetPosition() const noexcept
		{
			return m_Camera->GetPos();
		}
		/*
		* @brief	注視座標取得
		* @return	注視座標
		*/
		const Vector3& GetLookPosition() const noexcept
		{
			return m_Camera->GetLookPos();
		}
		/*
		* @brief	目標座標設定
		* @param	pos 目標座標
		*/
		void SetTargetPos(const Vector3& pos) noexcept
		{
			m_Camera->SetPos(pos);
		}
		/*
		* @brief	目標注視座標設定
		* @param	pos 目標注視座標
		*/
		void SetTargetLookPos(const Vector3& pos) noexcept
		{
			m_Camera->SetLookPos(pos);
		}
		/*
		* @brief	ターゲット設定
		* @param	pos 目標座標
		* @param	lookPos 目標注視座標
		*/
		void SetTarget(const Vector3& pos, const Vector3& lookPos) noexcept
		{
			SetTargetPos(pos);
			SetTargetLookPos(lookPos);
		}
		/*
		* @brief	カメラ取得
		* @return	カメラ
		*/
		const CCamera& GetCamera() const noexcept
		{
			return m_Camera->GetCamera();
		}

		/*
		* @brief	カメラ振動
		* @param	power	振動する幅
		* @param	freq	振動する頻度
		* @param	time	振動する時間 
		*/
		void Quake(float power, float freq, float time);
		/*
		* @brief	カメラ座標適用
		* @param	pos	座標
		* @param	lookPos	注視座標
		*/
		void Enable(const Vector3& pos, const Vector3& lookPos);

	};

}


//簡易アクセス用
#define CameraControllerInstance 	ActionGame::CameraController::GetInstance()

