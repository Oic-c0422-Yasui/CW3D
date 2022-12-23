#pragma once
#include "KnockBack.h"
#include "IActor.h"

namespace ActionGame
{
	/*
	* @brief	Y軸のみ固定の吸引ノックバック
	*/
	class FixedYInhaleKnockBack : public IKnockBack 
	{
	private:
		ActorPtr actor;
	public:
		FixedYInhaleKnockBack(const ActorPtr& actor)
			: actor(actor)
		{
		}
		Vector3 Get(const CVector3& otherPos) const override {
			CVector3 n = actor->GetPosition() - otherPos;
			n.Normal(n);
			n.y = 1;
			return n;
		}
	};
}