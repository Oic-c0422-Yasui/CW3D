#include "Object.h"

using namespace ActionGame;

CObject::CObject(const Vector3& pos, const Vector3& size, const Vector3& offset)
	: position_(pos)
	, size_(size)
	, offset_(offset)
	, isShow_(false)
{
}


void CObject::Initialize()
{
	isShow_ = true;

}

