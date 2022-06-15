#pragma once
#include "CameraBase.h"
class CInterpolateCamera : public CCameraBase
{
private:
	float m_Time;
	float m_CurrentTime;
	Sample::MyUtilities::ANIMV3_DATA m_PosAnim[2];
	Sample::MyUtilities::ANIMV3_DATA m_LookPosAnim[2];


public:
	CInterpolateCamera();
	~CInterpolateCamera();
	void Set(float time,Sample::MyUtilities::EASING_TYPE ease,const CameraPtr& camera);
	void Create() override;
	void Update(const Vector3& pos, const Vector3& lookPos) override;
};

using InterpolateCameraPtr = std::shared_ptr<CInterpolateCamera>;