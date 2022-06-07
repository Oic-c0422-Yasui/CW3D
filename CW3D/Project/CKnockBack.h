#pragma once
#include "Actor.h"
#include "Common.h"

namespace Sample
{
	class CKnockBack {
	public:
		virtual Vector3 Get(const CVector3& otherPos) const = 0;
	};

	class CFixedKnockBack : public CKnockBack {
	protected:
		bool rev;
	public:
		CFixedKnockBack(bool rev)
			: rev(rev)
		{
		}
		Vector3 Get(const CVector3& otherPos) {
			return rev ? Vector3(-1, 0, 0) : Vector3(1, 0, 0);
		}
	};

	class CAKnockBack : public CKnockBack {
	protected:
		ActorPtr actor;
	public:
		CAKnockBack(const ActorPtr& actor)
			: actor(actor)
		{
		}
		Vector3 Get(const CVector3& otherPos) {
			CVector3 n = actor->GetPosition() - otherPos;
			n.Normal(n);
			return n;
		}
	};
}

