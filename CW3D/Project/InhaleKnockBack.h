#pragma once
#include "KnockBack.h"
#include "IActor.h"

namespace ActionGame
{
	/*
	* @brief	吸引ノックバック
	*/
	class InhaleKnockBack : public IKnockBack 
	{
	private:
		ActorPtr actor;
	public:
		InhaleKnockBack(const ActorPtr& actor)
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