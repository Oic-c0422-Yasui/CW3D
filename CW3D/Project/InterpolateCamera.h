#pragma once
#include "CameraBase.h"

namespace ActionGame
{
	/*
	* @brief	カメラ切り替え時に補間を行う用のカメラ
	*/
	class CInterpolateCamera : public CameraBase
	{
	private:
		float endTime_;
		float currentTime_;
		CVector3 targetOffsetPos_;
		CVector3 targetOffsetLookPos_;
		MyUtil::ANIM_V3_DATA_ARRAY posAnim_;
		MyUtil::ANIM_V3_DATA_ARRAY lookPosAnim_;
		MyUtil::EASING_TYPE easeType_;

	public:
		CInterpolateCamera(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos);
		~CInterpolateCamera();
		void Set(float time,MyUtil::EASING_TYPE easeType,const CameraPtr& camera);
		void Create() override;
		void Update(const Vector3& pos, const Vector3& lookPos) override;
	};

	using InterpolateCameraPtr = std::shared_ptr<CInterpolateCamera>;
}
