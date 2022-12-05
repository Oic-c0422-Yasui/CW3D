#pragma once
#include "KnockBack.h"
#include "IActor.h"

namespace ActionGame
{
	//固定ノックバック
	class FixedKnockBack : public IKnockBack {
	private:
		ActorPtr actor;
	public:
		FixedKnockBack(const ActorPtr& actor)
			: actor(actor)
		{
		}

		Vector3 Get(const CVector3& otherPos) const override {
			return actor->IsReverse() ? Vector3(-1, 1, 1) : Vector3(1, 1, 1);
		}
	};
}