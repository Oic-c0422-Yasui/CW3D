#pragma once
#include "KnockBack.h"
#include "IActor.h"

namespace ActionGame
{
	/*
	* @brief	�z���m�b�N�o�b�N
	*/
	class CInhaleKnockBack : public IKnockBack 
	{
	private:
		ActorPtr actor_;
	public:
		CInhaleKnockBack(const ActorPtr& actor)
			: actor_(actor)
		{
		}
		Vector3 Get(const CVector3& otherPos) const override {
			CVector3 n = actor_->GetPosition() - otherPos;
			n.Normal(n);
			return n;
		}
	};
}