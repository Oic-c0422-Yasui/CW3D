#pragma once

#include "Shot.h"
#include "TemplateSingleton.h"
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

		void Create(Vector3 pos,float radius,int type)
		{
			auto add = std::make_shared<CShot>();
			m_Shots.push_back(add);
			add->Create(pos, radius, type);
		}

		void Delete()
		{
			auto removeIt = std::remove_if(m_Shots.begin(), m_Shots.end(), [&](const ShotPtr& shot) {
				return shot->IsShow() == false; });
			m_Shots.erase(removeIt, m_Shots.end());
		}


		void Update()
		{
			for (auto& shot : m_Shots)
			{
				shot->Update();
			}
		}



		ShotPtr& GetShot(int id) { return m_Shots[id]; }


	};
}
//簡易アクセス用
#define ShotManagerInstance 	Sample::CShotManager::GetInstance()

