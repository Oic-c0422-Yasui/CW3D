#pragma once
#include "CameraBase.h"
class CInterpolateCamera : public CCameraBase
{
private:
	float m_Time;
	float m_CurrentTime;
	CVector3 m_NextOffsetPos;
	CVector3 m_NextOffsetLookPos;
	Sample::MyUtilities::ANIMV3_DATA m_PosAnim[2];
	Sample::MyUtilities::ANIMV3_DATA m_LookPosAnim[2];
	Sample::MyUtilities::EASING_TYPE m_Ease;

public:
	CInterpolateCamera(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos);
	~CInterpolateCamera();
	void Set(float time,Sample::MyUtilities::EASING_TYPE ease,const CameraPtr& camera);
	void Create() override;
	void Update(const Vector3& pos, const Vector3& lookPos) override;
};

using InterpolateCameraPtr = std::shared_ptr<CInterpolateCamera>;