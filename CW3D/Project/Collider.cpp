#include "Collider.h"

ActionGame::CCollider::CCollider()
	: position_(0,0,0)
	, size_(0,0,0)
{
}

ActionGame::CCollider::CCollider(Vector3 pos, Vector3 size)
	: position_(pos)
	, size_(size)
{
	collider_.SetPosition(pos);
	collider_.Size = size;
}

ActionGame::CCollider::~CCollider()
{
}

ActionGame::Collider ActionGame::CCollider::GetCollider() const noexcept
{
	Collider collider(position_,size_);

	return collider;
}

const Vector3& ActionGame::CCollider::GetPosition() const noexcept
{
	return position_;
}

const Vector3& ActionGame::CCollider::GetSize() const noexcept
{
	return size_;
}

void ActionGame::CCollider::SetCollider(const Vector3& pos, const Vector3& size) noexcept
{
	SetPosition(pos);
	SetSize(size);
}

void ActionGame::CCollider::SetSize(const Vector3& size) noexcept
{
	size_ = size;
}

void ActionGame::CCollider::SetPosition(const Vector3& pos) noexcept
{
	position_ = pos;
}
