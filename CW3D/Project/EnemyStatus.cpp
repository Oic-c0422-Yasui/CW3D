#include "EnemyStatus.h"

using namespace ActionGame;

ActionGame::EnemyStatus::EnemyStatus(int hp, float ultGauge, float ultGaugeBoostMag, int atk, const std::string& meshName, const Vector3& colliderSize, float colliderHeight)
	: m_Hp(hp)
	, m_UltGauge(ultGauge)
	, m_UltGaugeBoostMag(ultGaugeBoostMag)
	, m_Atk(atk)
	, m_MeshName(meshName)
	, m_ColliderSize(colliderSize)
	, m_ColliderHeight(colliderHeight)
{
}

ActionGame::EnemyStatusDictionary::EnemyStatusDictionary()
{
}

void ActionGame::EnemyStatusDictionary::Add(const std::string& name, const EnemyStatusPtr& status)
{
	map[name] = status;
}

const EnemyStatusPtr& ActionGame::EnemyStatusDictionary::Get(const std::string& name)
{
	if (IsContain(name))
	{
		return map[name];
	}
	return nullptr;
}

bool ActionGame::EnemyStatusDictionary::Delete(const std::string& name)
{
	auto it = map.find(name);
	if (it != map.end())
	{
		map.erase(it);
		return true;
	}
	return false;
}

bool ActionGame::EnemyStatusDictionary::IsContain(const std::string& name)
{
	auto it = map.find(name);
	return it != map.end();
}