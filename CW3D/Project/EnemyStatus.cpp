#include "EnemyStatus.h"

using namespace ActionGame;


ActionGame::EnemyStatusDictionary::EnemyStatusDictionary()
{
}

void ActionGame::EnemyStatusDictionary::Add(const std::string& name, const EnemyStatusPtr& status)
{
	map_[name] = status;
}

const EnemyStatusPtr& ActionGame::EnemyStatusDictionary::Get(const std::string& name)
{
	if (IsContain(name))
	{
		return map_[name];
	}
	return nullptr;
}

bool ActionGame::EnemyStatusDictionary::Delete(const std::string& name)
{
	auto it = map_.find(name);
	if (it != map_.end())
	{
		map_.erase(it);
		return true;
	}
	return false;
}

bool ActionGame::EnemyStatusDictionary::IsContain(const std::string& name)
{
	auto it = map_.find(name);
	return it != map_.end();
}