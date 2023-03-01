#pragma once
#include "CameraBase.h"

namespace ActionGame
{
	/*
	* @brief	í èÌÉJÉÅÉâ
	*/
	class CNormalCamera :public CameraBase
	{
	private:
	public:
		CNormalCamera(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos);
		~CNormalCamera();
		void Create() override;
		void Update(const Vector3& pos, const Vector3& lookPos) override;
		void Enable(const Vector3& pos, const Vector3& lookPos) override;
	
	};
}



