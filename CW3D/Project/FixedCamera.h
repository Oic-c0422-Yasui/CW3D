#pragma once
#include "CameraBase.h"
#include "TimeScaleController.h"

/*
* @brief	å≈íËÉJÉÅÉâ
*/
class FixedCamera :  public CCameraBase
{
public:
	FixedCamera(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos);
	~FixedCamera();
	void Create() override;
	void Update(const Vector3& pos, const Vector3& lookPos) override;
};

using FixedCameraPtr = std::shared_ptr<FixedCamera>();


