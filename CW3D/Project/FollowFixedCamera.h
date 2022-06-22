#pragma once
#include "CameraBase.h"
class CFollowFixedCamera : public CCameraBase
{
public:
	CFollowFixedCamera(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos);
	~CFollowFixedCamera();
	void Create() override;
	void Update(const Vector3& pos, const Vector3& lookPos) override;
};

