#pragma once
#include "KnockBack.h"
#include "IActor.h"

namespace Sample
{
	class CInhaleKnockBack : public CKnockBack {
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
	using InhaleKnockBackPtr = std::shared_ptr<CInhaleKnockBack>;
}