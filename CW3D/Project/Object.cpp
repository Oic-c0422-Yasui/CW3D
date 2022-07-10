#include "Object.h"

using namespace Sample;

CObject::CObject(const Vector3& pos, const Vector3& size, const Vector3& offset)
	: m_Position(pos)
	, m_Size(size)
	, m_Offset(offset)
	, m_ShowFlg(false)
{
}

CObject::~CObject()
{
}

bool CObject::Load()
{
	return true;
}

void CObject::Initialize()
{
	m_ShowFlg = true;

}

void CObject::Update()
{
}

void CObject::Render()
{
}

void CObject::Release()
{
}
