#pragma once

#include "Common.h"

namespace ActionGame
{
	using BoneState = LPBONEMOTIONSTATE;
	using Matrix = Matrix44;

	class CShadow
	{
	private:
		std::shared_ptr<CMeshContainer> mesh_;
		CMatrix44	matrix_;
		float attenuationRate_;		//âeï\é¶ÇÃå∏êäó¶
		float attenuationDistance_;	//âeï\é¶å∏êäãóó£
	public:
		CShadow();
		~CShadow();
		bool Load();
		void Initialize(const BoneState& bone, const Vector3& scale);
		void Initialize(const BoneState& bone, const Vector3& scale,float attenuationDistance);
		void Update(const BoneState& bone,const Vector3& pos);
		void Render(const Vector4& color);
		void Release();
	};
}


