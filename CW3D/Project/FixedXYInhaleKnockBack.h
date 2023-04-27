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
			float n = actor_->GetPosition().z - otherPos.z;
			float d = 1 / std::sqrtf(n * n);
			n *= d;
			
			return actor_->IsReverse() ? Vector3(-1, 1, n) : Vector3(1, 1, n);
		}
	};
}