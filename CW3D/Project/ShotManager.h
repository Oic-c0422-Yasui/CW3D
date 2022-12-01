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
		/*
		* @brief	’e‚ğ¶¬‚·‚é(‹…‘Ì)
		* @param	pos	¶¬À•W
		* @param	sphere	‹…‘Ì‚Ì’e
		* @return	¶¬‚³‚ê‚½’e
		*/
		ShotPtr Create(const Vector3& pos, const ShotSphere& sphere);
		/*
		* @brief	’e‚ğ¶¬‚·‚é(lŠp)
		* @param	pos	¶¬À•W
		* @param	aabb	lŠp‚Ì’e
		* @return	¶¬‚³‚ê‚½’e
		*/
		ShotPtr Create(const Vector3& pos, const ShotAABB& aabb);

		/*
		* @brief	”ñ•\¦‚Ì’e‚ğíœ‚·‚é
		*/
		void Delete();

		/*
		* @brief	’e‚ğ”ñ•\¦‚É‚·‚é
		*/
		void Reset();

		/*
		* @brief	XV
		*/
		void Update();
		/*
		* @brief	•`‰æ
		*/
		void Render();


		/*
		* @brief	’e‚ğæ“¾‚·‚é
		* @param	id ’e‚Ì”z—ñ”Ô†
		* @return	’e
		*/
		const ShotPtr& GetShot(size_t id) 
		{
			assert(m_Shots[id]);
			return m_Shots[id]; 
		}

		/*
		* @brief	’e‚ğ”‚ğæ“¾‚·‚é
		* @param	’e‚Ì”
		*/
		size_t GetShotCount()
		{
			return m_Shots.size();
		}

	};
}
//ŠÈˆÕƒAƒNƒZƒX—p
#define ShotManagerInstance 	Sample::CShotManager::GetInstance()

