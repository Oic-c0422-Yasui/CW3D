#include "Object.h"

using namespace ActionGame;

CObject::CObject(const Vector3& pos, const Vector3& size, const Vector3& offset)
	: position_(pos)
	, m_Size(size)
	, offset_(offset)
	, m_ShowFlg(false)
{
}


void CObject::Initialize()
{
	m_ShowFlg = true;

}

