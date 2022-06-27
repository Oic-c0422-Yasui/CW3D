#pragma once
#include "CameraBase.h"
class CNomalCamera :public CCameraBase
{
private:
public:
	CNomalCamera(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos);
	~CNomalCamera();
	void Create() override;
	void Update(const Vector3& pos, const Vector3& lookPos) override;
	void Enable(const Vector3& pos, const Vector3& lookPos) override;
	
};


