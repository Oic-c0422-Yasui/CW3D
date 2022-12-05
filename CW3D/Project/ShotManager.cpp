#include "ShotManager.h"

using namespace ActionGame;

ShotPtr ActionGame::CShotManager::Create(const Vector3& pos, const ShotSphere& sphere)
{
	auto add = std::make_shared<CShot>();
	m_Shots.push_back(add);
	add->Create(pos, sphere);
	return add;
}

ShotPtr ActionGame::CShotManager::Create(const Vector3& pos, const ShotAABB& aabb)
{
	auto add = std::make_shared<CShot>();
	m_Shots.push_back(add);
	add->Create(pos, aabb);
	return add;
}

void ActionGame::CShotManager::Delete()
{
	auto removeIt = std::remove_if(m_Shots.begin(), m_Shots.end(), [&](const ShotPtr& shot) {
		return shot->IsShow() == false; });
	m_Shots.erase(removeIt, m_Shots.end());
}

void ActionGame::CShotManager::Reset()
{
	m_Shots.clear();
}

void ActionGame::CShotManager::Update()
{
	for (auto& shot : m_Shots)
	{
		shot->Update();
	}
}

void ActionGame::CShotManager::Render()
{
	for (auto& shot : m_Shots)
	{
		shot->Render();
	}
}
