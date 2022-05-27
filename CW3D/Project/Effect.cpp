#include "Effect.h"
#include "EffectManager.h"

namespace Sample
{
	

	CEffect::~CEffect()
	{
	}

	void CEffect::Initialize()
	{
		m_Position = Vector3(0, 0, 0);
	}

	void CEffect::Update()
	{
		if (!EffectManagerInstance.GetManager()->Exists(m_Handle))
		{
			m_StopFlg = true;
		}
		if (m_StopFlg)
		{
			EffectManagerInstance.GetManager()->StopEffect(m_Handle);
		}
	}

}