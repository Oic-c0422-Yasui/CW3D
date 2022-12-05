#include "Object.h"

using namespace ActionGame;

CObject::CObject(const Vector3& pos, const Vector3& size, const Vector3& offset)
	: m_Position(pos)
	, m_Size(size)
	, m_Offset(offset)
	, m_ShowFlg(false)
{
}


void CObject::Initialize()
{
	m_ShowFlg = true;

}

