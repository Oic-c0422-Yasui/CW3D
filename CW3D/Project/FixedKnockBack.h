#pragma once
#include "KnockBack.h"
#include "IActor.h"

namespace ActionGame
{
	//�Œ�m�b�N�o�b�N
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