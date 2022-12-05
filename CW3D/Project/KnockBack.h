#pragma once
#include "Common.h"


namespace ActionGame
{
	class IKnockBack {
	public:
		virtual Vector3 Get(const CVector3& otherPos) const = 0;
	};
	using KnockBackPtr = std::shared_ptr<IKnockBack>;
}

	



	