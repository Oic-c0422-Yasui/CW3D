#include "Effect.h"
#include "EffectRenderer.h"

namespace ActionGame
{
	Effect::Effect(Effekseer::Handle handle)
		: effect_()
		, handle_(handle)
		, isStop_(false)
	{

	}
	Effect::~Effect()
	{
	}

	void Effect::Initialize( const Vector3& offset)
	{
		offset_ = offset;
	}

	void Effect::Update()
	{
		if (!EffectRendererInstance.GetManager()->Exists(handle_))
		{
			isStop_ = true;
		}
		if (isStop_)
		{
			EffectRendererInstance.GetManager()->StopEffect(handle_);
		}
	}
}