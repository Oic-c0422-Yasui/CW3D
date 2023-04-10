#include "Effect.h"
#include "EffectRenderer.h"

namespace ActionGame
{
	CEffect::CEffect(Effekseer::Handle handle)
		: effect_()
		, handle_(handle)
		, isStop_(false)
	{

	}
	CEffect::~CEffect()
	{
		effect_.Reset();
	}

	void CEffect::Initialize( const Vector3& offset)
	{
		offset_ = offset;
	}

	void CEffect::Update()
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