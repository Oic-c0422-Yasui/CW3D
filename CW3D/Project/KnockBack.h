#pragma once
#include "Actor.h"
#include "Common.h"

namespace Sample
{
	class CKnockBack {

	public:
		virtual Vector3 Get(const CVector3& otherPos) const = 0;
	};
	using KnockBackPtr = std::shared_ptr<CKnockBack>;

	class CFixedKnockBack : public CKnockBack {
	protected:
		ActorPtr actor;
	public:
		CFixedKnockBack(const ActorPtr& actor)
			: actor(actor)
		{
		}

		 Vector3 Get(const CVector3& otherPos) const override {
			return actor->IsReverse() ? Vector3(-1, 0, 0) : Vector3(1, 0, 0);
		}
	};
	using FixedKnockBackPtr = std::shared_ptr<CFixedKnockBack>;

	class CInhaleKnockBack : public CKnockBack {
	protected:
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

