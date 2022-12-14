#pragma once

#include "ActorObject.h"
#include "Singleton.h"



namespace ActionGame
{


	class CActorObjectManager : public Singleton<CActorObjectManager>
	{
		friend class Singleton<CActorObjectManager>;
	private:

		using ActorMap = std::unordered_map<unsigned int, ActorObjectWeakPtr>;
		using ActorMapPtr = std::shared_ptr<ActorMap>;
		
		using TagMap = std::unordered_map<CHARACTER_TYPE, ActorMapPtr>;

		TagMap m_Tags;

		CActorObjectManager()
			: Singleton<CActorObjectManager>()
			, m_Tags()
		{
		}

	public:

		void Add(const ActorObjectPtr& actor)
		{
			auto& tagActors = m_Tags[actor->GetType()];
			if (tagActors == nullptr)
			{
				tagActors = std::make_shared< ActorMap>();
				m_Tags[actor->GetType()] = tagActors;
			}
			(*tagActors)[actor->GetID()] = actor;
			
		}

		void Delete()
		{

			for (auto& map : m_Tags)
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

		ActorObjectPtr GetActor(int id) {
			for (auto& map : m_Tags)
			{
				auto& it = map.second->find(id);
				if (it != map.second->end())
				{
					return it->second.lock();
				}
			}
			return nullptr;
		}

		ActorObjectPtr GetActor(CHARACTER_TYPE type,int id) {
			return (*m_Tags[type])[id].lock();
		}

	};
}
//簡易アクセス用
#define ActorObjectManagerInstance 	ActionGame::CActorObjectManager::GetInstance()

