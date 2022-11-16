#pragma once
#include "KnockBack.h"
#include "IActor.h"

namespace Sample
{
	//吸引ノックバック
	class CInhaleKnockBack : public IKnockBack {
	private:
		ActorPtr actor;
	public:
		CInhaleKnockBack(const ActorPtr& actor)
			: actor(actor)
		{
		}
		Vector3 Get(const CVector3& otherPos) const override {
			CVector3 n = actor->GetPosition() - otherPos;
			n.Normal(n);
			return n;
		}
	};
}