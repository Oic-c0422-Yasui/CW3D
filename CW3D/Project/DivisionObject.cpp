#include "DivisionObject.h"

using namespace ActionGame;

ActionGame::CDivisionObject::CDivisionObject(const Vector3& pos, const Vector3& size, const Vector3& offset)
	: CObject(pos, size, offset)
{
}

ActionGame::CDivisionObject::~CDivisionObject()
{
	Release();
}

bool ActionGame::CDivisionObject::Load()
{
	return true;
}

void ActionGame::CDivisionObject::Initialize()
{
	CObject::Initialize();
	m_pEffect = EffectControllerInstance.Play(param.name, GetCollider().Position, param); 
}

void ActionGame::CDivisionObject::Update()
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

void ActionGame::CDivisionObject::Render()
{
}

void ActionGame::CDivisionObject::Release()
{
	m_pEffect.reset();
}
