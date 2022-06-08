#pragma once
#include "Common.h"


namespace Sample
{
	class CKnockBack {
	protected:
	public:
		virtual Vector3 Get(const CVector3& otherPos) const = 0;
	};
	using KnockBackPtr = std::shared_ptr<CKnockBack>;
}

	



	