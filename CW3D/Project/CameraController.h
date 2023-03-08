#pragma once
#include "Singleton.h"
#include "CameraBase.h"


namespace ActionGame
{
	/*
	* @brief	カメラ操作クラス
	*/
	class CCameraController : public Singleton<CCameraController>
	{
		friend class Singleton<CCameraController>;
	private:

		CameraPtr	camera_;
		CameraPtr	nextCamera_;
		CameraPtr	defaultCamera_;
		bool		isLeap_;
		bool		isLeapStart_;
		float		leapTime_;
		bool		isLeapEnd_;
		float		leapEndTime_;
		MyUtil::EASING_TYPE endEaseType_;
		float		timeScale_;
		float		currentTime_;
		bool		isTimerStart_;


		//カメラ揺れ
		struct QuakeState
		{
			float power;
			float frequent;
			float time;
			float currentTime;
		};
		QuakeState quakeState_;

		Vector3		targetPos_;
		Vector3		targetLookPos_;
		
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
		void SetCamera(const CameraPtr& camera, float tTime, MyUtil::EASING_TYPE startEaseType, float leapStartTime, MyUtil::EASING_TYPE endEaseType, float leapEndTime);
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
			return camera_->GetPosition();
		}
		/*
		* @brief	注視座標取得
		* @return	注視座標
		*/
		const Vector3& GetLookPosition() const noexcept
		{
			return camera_->GetLookPos();
		}
		/*
		* @brief	目標座標設定
		* @param	pos 目標座標
		*/
		void SetTargetPos(const Vector3& pos) noexcept
		{
			camera_->SetPos(pos);
		}
		/*
		* @brief	目標注視座標設定
		* @param	pos 目標注視座標
		*/
		void SetTargetLookPos(const Vector3& pos) noexcept
		{
			camera_->SetLookPos(pos);
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
			return camera_->GetCamera();
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

		/*
		* @brief	カメラの投影行列設定を取得する
		* @return	投影行列設定
		*/
		const PerspectiveParam& GetPerspectiveParam() const noexcept;
	};

}


//簡易アクセス用
#define CameraControllerInstance 	ActionGame::CCameraController::GetInstance()

