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
		//m_Handle = CEffectManager::GetInstance().Play(エフェクト指定);
	}

	void CEffect::Update()
	{
		if (!CEffectManager::GetInstance().GetManager()->Exists(m_Handle))
		{
			m_StopFlg = true;
		}
	}

}