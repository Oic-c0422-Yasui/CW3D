#pragma once
#include "CameraBase.h"

namespace ActionGame
{
	/*
	* @brief	�ʏ�J����
	*/
	class NomalCamera :public CameraBase
	{
	private:
	public:
		NomalCamera(const Vector3& pos, const Vector3& lookPos, const Vector3& offsetPos, const Vector3& offsetLookPos);
		~NomalCamera();
		void Create() override;
		void Update(const Vector3& pos, const Vector3& lookPos) override;
		void Enable(const Vector3& pos, const Vector3& lookPos) override;
	
	};
}



