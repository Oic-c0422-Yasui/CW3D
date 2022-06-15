#pragma once
#include "CameraBase.h"
class CNomalCamera :public CCameraBase
{
public:
	CNomalCamera();
	~CNomalCamera();
	void Create() override;
	void Update(const Vector3& pos, const Vector3& lookPos) override;
};


