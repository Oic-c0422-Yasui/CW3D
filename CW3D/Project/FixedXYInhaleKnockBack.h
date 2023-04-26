#
#pragma once
#include "KnockBack.h"
#include "IActor.h"

namespace ActionGame
{
	/*
	* @brief	XY軸固定の吸引ノックバック
	*/
	class CFixedXYInhaleKnockBack : public IKnockBack
	{
	private:
		ActorPtr actor_;
	public:
		CFixedXYInhaleKnockBack(const ActorPtr& actor)
			: actor_(actor)
		{
		}
		Vector3 Get(const CVector3& otherPos) const override {
			CVector3 n = actor_->GetPosition() - otherPos;
			n.Normal(n);
			n.x = 1;
			n.y = 1;
			return actor_->IsReverse() ? Vector3(-n.x, n.y, n.z) : Vector3(n.x, n.y, n.z);
		}
	};
}