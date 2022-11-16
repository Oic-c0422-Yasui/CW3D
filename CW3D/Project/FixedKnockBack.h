#pragma once
#include "KnockBack.h"
#include "IActor.h"

namespace Sample
{
	//固定ノックバック
	class CFixedKnockBack : public IKnockBack {
	private:
		ActorPtr actor;
	public:
		CFixedKnockBack(const ActorPtr& actor)
			: actor(actor)
		{
		}

		Vector3 Get(const CVector3& otherPos) const override {
			return actor->IsReverse() ? Vector3(-1, 1, 1) : Vector3(1, 1, 1);
		}
	};
}