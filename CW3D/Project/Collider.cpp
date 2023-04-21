#include "Collider.h"

ActionGame::CCollider::CCollider()
	: collider_()
	, position_(0,0,0)
	, size_(0,0,0)
{
}

ActionGame::CCollider::CCollider(Vector3 pos, Vector3 size,Vector3 offset)
	: collider_()
	, position_(pos)
	, size_(size)
	, offset_(offset)
{
}

ActionGame::CCollider::~CCollider()
{
}

const ActionGame::Collider& ActionGame::CCollider::GetCollider() noexcept
{
	collider_ = Collider(position_ + offset_, size_);
	return collider_;
}

const Vector3& ActionGame::CCollider::GetPosition() const noexcept
{
	return position_ + offset_;
}

const Vector3& ActionGame::CCollider::GetSize() const noexcept
{
	return size_;
}

void ActionGame::CCollider::SetPosition(const Vector3& pos) noexcept
{
	position_ = pos;
}

void ActionGame::CCollider::SetSize(const Vector3& size) noexcept
{
	size_ = size;
}

void ActionGame::CCollider::SetOffset(const Vector3& offset) noexcept
{
	offset_ = offset;
}



void ActionGame::CCollider::SetCollider(const Vector3& pos,const Vector3& offset, const Vector3& size) noexcept
{
	position_ = pos;
	size_ = size;
	offset_ = offset;
	collider_ = Collider(position_ + offset_, size_);
}

