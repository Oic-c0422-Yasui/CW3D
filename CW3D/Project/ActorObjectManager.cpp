#include "ActorObjectManager.h"

void ActionGame::CActorObjectManager::Add(const ActorObjectPtr& actor)
{
	auto& tagActors = tagMap_[actor->GetType()];
	if (tagActors == nullptr)
	{
		tagActors = std::make_shared< ActorMap>();
		tagMap_[actor->GetType()] = tagActors;
	}
	(*tagActors)[actor->GetID()] = actor;

}

void ActionGame::CActorObjectManager::Delete()
{
	for (auto& map : tagMap_)
	{
		for (auto it = map.second->begin(); it != map.second->end(); )
		{
			auto here = it++;
			if (here->second.expired())
			{
				map.second->erase(here);
			}
		}
	}

}

ActionGame::ActorObjectPtr ActionGame::CActorObjectManager::GetActor(uint32_t id)
{
	for (auto& map : tagMap_)
	{
		auto& it = map.second->find(id);
		if (it != map.second->end())
		{
			return it->second.lock();
		}
	}
	return nullptr;
}
void ActionGame::CActorObjectManager::AddActorList(CHARA_TYPE type, ActorObjectWeakListPtr& list)
{
	//指定したタイプのアクターが存在しているか？
	auto it = tagMap_.find(type);
	if (it == tagMap_.end())
	{
		return;
	}

	for (auto map : (*tagMap_[type]))
	{
		list->push_back(map.second.lock());
	}
}

ActionGame::ActorObjectWeakListPtr ActionGame::CActorObjectManager::GetActors(CHARA_TYPE type)
{
	ActorObjectWeakListPtr list = std::make_shared<ActorObjectWeakList>();
	AddActorList(type, list);
	return list;
}

ActionGame::ActorObjectWeakListPtr ActionGame::CActorObjectManager::GetHostilityActors(CHARA_TYPE type)
{
	ActorObjectWeakListPtr list = std::make_shared<ActorObjectWeakList>();

	switch (type)
	{
	case CHARA_TYPE::PLAYER:
		AddActorList(CHARA_TYPE::ENEMY, list);
		AddActorList(CHARA_TYPE::BOSS, list);
		break;
	case CHARA_TYPE::ENEMY:
		AddActorList(CHARA_TYPE::PLAYER, list);
		break;
	case CHARA_TYPE::BOSS:
		AddActorList(CHARA_TYPE::PLAYER, list);
		break;
	default:
		return nullptr;
	}

	
	return list;
}
