#pragma once
#include "CameraBase.h"

namespace ActionGame
{
	/*
	* @brief	å≈íËÉJÉÅÉâ
	*/
	class CFixedCamera :  public CameraBase
	{
	public:
		CFixedCamera(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos);
		~CFixedCamera();
		void Create() override;
		void Update(const Vector3& pos, const Vector3& lookPos) override;
	};

	using FixedCameraPtr = std::shared_ptr<CFixedCamera>();
}



