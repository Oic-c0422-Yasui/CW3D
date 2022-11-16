#pragma once
#include "KnockBack.h"
#include "IActor.h"

namespace Sample
{
	//�z���m�b�N�o�b�N
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