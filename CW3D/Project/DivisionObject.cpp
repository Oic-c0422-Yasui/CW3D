#include "DivisionObject.h"

using namespace Sample;

Sample::CDivisionObject::CDivisionObject(const Vector3& pos, const Vector3& size, const Vector3& offset)
	: CObject(pos, size, offset)
{
}

Sample::CDivisionObject::~CDivisionObject()
{
	Release();
}

bool Sample::CDivisionObject::Load()
{
	return true;
}

void Sample::CDivisionObject::Initialize()
{
	CObject::Initialize();
	m_pEffect = EffectControllerInstance.Play(param.name, GetCollider().Position, param); 
}

void Sample::CDivisionObject::Update()
{
	if (!m_ShowFlg)
	{
		if (!m_pEffect->IsStop())
		{
			m_pEffect->SetStop(true);
		}
		return;
	}
	if (m_pEffect->IsStop())
	{
		m_pEffect = EffectControllerInstance.Play(param.name, GetCollider().Position, param);
	}
}

void Sample::CDivisionObject::Render()
{
}

void Sample::CDivisionObject::Release()
{
	m_pEffect.reset();
}
