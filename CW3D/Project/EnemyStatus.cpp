#include "EnemyStatus.h"

using namespace ActionGame;


ActionGame::EnemyStatusDictionary::EnemyStatusDictionary()
{
}

void ActionGame::EnemyStatusDictionary::Add(const std::string& name, const EnemyStatusPtr& status)
{
	m_Map[name] = status;
}

const EnemyStatusPtr& ActionGame::EnemyStatusDictionary::Get(const std::string& name)
{
	if (IsContain(name))
	{
		return m_Map[name];
	}
	return nullptr;
}

bool ActionGame::EnemyStatusDictionary::Delete(const std::string& name)
{
	auto it = m_Map.find(name);
	if (it != m_Map.end())
	{
		m_Map.erase(it);
		return true;
	}
	return false;
}

bool ActionGame::EnemyStatusDictionary::IsContain(const std::string& name)
{
	auto it = m_Map.find(name);
	return it != m_Map.end();
}