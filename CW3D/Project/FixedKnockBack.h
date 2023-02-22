#pragma once
#include "KnockBack.h"
#include "IActor.h"

namespace ActionGame
{
	/*
	* @brief	�Œ�l�m�b�N�o�b�N
	*/
	class CFixedKnockBack : public IKnockBack {
	private:
		ActorPtr actor_;
	public:
		CFixedKnockBack(const ActorPtr& actor)
			: actor_(actor)
		{
		}

		Vector3 Get(const CVector3& otherPos) const override {
			return actor_->IsReverse() ? Vector3(-1, 1, 1) : Vector3(1, 1, 1);
		}
	};
}