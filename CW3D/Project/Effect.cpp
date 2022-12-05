#include "Effect.h"
#include "EffectRenderer.h"

namespace ActionGame
{
	Effect::Effect(Effekseer::Handle handle)
		: m_Effect()
		, m_Handle(handle)
		, m_StopFlg(false)
	{

	}
	Effect::~Effect()
	{
	}

	void Effect::Initialize( const Vector3& offset)
	{
		m_Offset = offset;
	}

	void Effect::Update()
	{
		if (!EffectRendererInstance.GetManager()->Exists(m_Handle))
		{
			m_StopFlg = true;
		}
		if (m_StopFlg)
		{
			EffectRendererInstance.GetManager()->StopEffect(m_Handle);
		}
	}
}