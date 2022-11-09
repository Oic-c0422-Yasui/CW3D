#pragma once

#include "Shot.h"
#include "Singleton.h"
#include "Common.h"


namespace Sample
{
	

	class CShotManager : public Singleton<CShotManager>
	{
		friend class Singleton<CShotManager>;
	private:
		std::vector<ShotPtr> m_Shots;

		CShotManager()
			: Singleton<CShotManager>()
			, m_Shots()
		{
		}

	public:

		ShotPtr Create(Vector3 pos,ShotSphere sphere)
		{
			auto add = std::make_shared<CShot>();
			m_Shots.push_back(add);
			add->Create(pos, sphere);
			return add;
		}

		ShotPtr Create(Vector3 pos, ShotAABB aabb)
		{
			auto add = std::make_shared<CShot>();
			m_Shots.push_back(add);
			add->Create(pos, aabb);
			return add;
		}

		void Delete()
		{
			auto removeIt = std::remove_if(m_Shots.begin(), m_Shots.end(), [&](const ShotPtr& shot) {
				return shot->IsShow() == false; });
			m_Shots.erase(removeIt, m_Shots.end());
		}

		void Reset()
		{
			for (auto& shot : m_Shots)
			{
				shot->SetShow(false);
			}
		}

		void Update()
		{
			for (auto& shot : m_Shots)
			{
				shot->Update();
			}
		}

		void Render()
		{
			for (auto& shot : m_Shots)
			{
				shot->Render();
			}
		}



		const ShotPtr& GetShot(int id) {
			assert(m_Shots[id]);
			return m_Shots[id]; }

		size_t GetShotSize()
		{
			return m_Shots.size();
		}

	};
}
//簡易アクセス用
#define ShotManagerInstance 	Sample::CShotManager::GetInstance()

