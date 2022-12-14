#pragma once
#include "CameraBase.h"

namespace ActionGame
{
	class FollowFixedCamera : public CameraBase
	{
	public:
		FollowFixedCamera(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos);
		~FollowFixedCamera();
		void Create() override;
		void Update(const Vector3& pos, const Vector3& lookPos) override;
	};
}



