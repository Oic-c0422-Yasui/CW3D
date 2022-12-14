#pragma once
#include "CameraBase.h"

namespace ActionGame
{
	/*
	* @brief	ï‚ä‘ópÉJÉÅÉâ
	*/
	class InterpolateCamera : public CameraBase
	{
	private:
		float m_Time;
		float m_CurrentTime;
		CVector3 m_NextOffsetPos;
		CVector3 m_NextOffsetLookPos;
		MyUtilities::ANIM_V3_DATA_ARRAY m_PosAnim;
		MyUtilities::ANIM_V3_DATA_ARRAY m_LookPosAnim;
		MyUtilities::EASING_TYPE m_Ease;

	public:
		InterpolateCamera(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos);
		~InterpolateCamera();
		void Set(float time,MyUtilities::EASING_TYPE ease,const CameraPtr& camera);
		void Create() override;
		void Update(const Vector3& pos, const Vector3& lookPos) override;
	};

	using InterpolateCameraPtr = std::shared_ptr<InterpolateCamera>;
}
