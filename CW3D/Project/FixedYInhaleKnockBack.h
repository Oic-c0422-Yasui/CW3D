#pragma once
#include "KnockBack.h"
#include "IActor.h"

namespace ActionGame
{
	/*
	* @brief	Y軸のみ固定の吸引ノックバック
	*/
	class CFixedYInhaleKnockBack : public IKnockBack 
	{
	private:
		ActorPtr actor_;
	public:
		CFixedYInhaleKnockBack(const ActorPtr& actor)
			: actor_(actor)
		{
		}
		Vector3 Get(const CVector3& otherPos) const override {
			CVector3 n = actor_->GetPosition() - otherPos;
			n.Normal(n);
			n.y = 1;
			return n;
		}
	};
}