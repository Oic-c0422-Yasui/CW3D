#include "Effect.h"
#include "EffectManager.h"

namespace Sample
{
	

	CEffect::~CEffect()
	{
	}

	void CEffect::Initialize( const Vector3& offset)
	{
		m_Offset = offset;
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