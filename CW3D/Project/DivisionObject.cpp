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
	effect_ = EffectControllerInstance.Play(effectParam_.name, GetCollider().Position, effectParam_);
}

void ActionGame::CDivisionObject::Update()
{
	if (!isShow_)
	{
		if (!effect_->IsStop())
		{
			effect_->SetStop(true);
		}
		return;
	}
	if (effect_->IsStop() || effect_ == nullptr)
	{
		effect_ = EffectControllerInstance.Play(effectParam_.name, GetCollider().Position, effectParam_);
	}
}

void ActionGame::CDivisionObject::Render()
{
}

void ActionGame::CDivisionObject::Release()
{
	effect_.reset();
}
