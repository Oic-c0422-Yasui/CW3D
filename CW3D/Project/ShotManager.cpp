#include "ShotManager.h"

using namespace ActionGame;

ShotPtr ActionGame::CShotManager::Create(const Vector3& pos, const ShotSphere& sphere)
{
	auto add = std::make_shared<Shot>();
	shotArray_.push_back(add);
	add->Create(pos, sphere);
	return add;
}

ShotPtr ActionGame::CShotManager::Create(const Vector3& pos, const ShotAABB& aabb)
{
	auto add = std::make_shared<Shot>();
	shotArray_.push_back(add);
	add->Create(pos, aabb);
	return add;
}

ShotPtr ActionGame::CShotManager::Create(const Vector3& pos, const ShotOBB& obb)
{
	auto add = std::make_shared<Shot>();
	shotArray_.push_back(add);
	add->Create(pos, obb);
	return add;
}

void ActionGame::CShotManager::Delete()
{
	auto removeIt = std::remove_if(shotArray_.begin(), shotArray_.end(), [&](const ShotPtr& shot) {
		return shot->IsShow() == false; });
	shotArray_.erase(removeIt, shotArray_.end());
}

void ActionGame::CShotManager::Reset()
{
	for (auto& shot : shotArray_)
	{
		shot->SetShow(false);
	}
}

void ActionGame::CShotManager::Update()
{
	for (auto& shot : shotArray_)
	{
		shot->Update();
	}
}

void ActionGame::CShotManager::Render()
{
	for (auto& shot : shotArray_)
	{
		shot->Render();
	}
}
