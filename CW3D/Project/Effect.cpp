#include "Effect.h"


namespace Sample
{
	

	CEffect::~CEffect()
	{
	}

	void CEffect::Initialize()
	{
		m_Position = Vector3(0, 0, 0);
		//m_Handle = CEffectManager::GetInstance().Play(�G�t�F�N�g�w��);
	}

	void CEffect::Update()
	{
	}

	void CEffect::Render()
	{
	}

	void CEffect::RenderDebug()
	{
	}

	void CEffect::Render2DDebug()
	{
	}

	void CEffect::Release()
	{
	}

}