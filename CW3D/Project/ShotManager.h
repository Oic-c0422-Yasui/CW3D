#pragma once

#include "Shot.h"
#include "Singleton.h"
#include "Common.h"


namespace ActionGame
{
	

	class CShotManager : public Singleton<CShotManager>
	{
		friend class Singleton<CShotManager>;
	private:
		std::vector<ShotPtr> shotArray_;

		CShotManager()
			: Singleton<CShotManager>()
			, shotArray_()
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
		* @brief	’e‚ğ¶¬‚·‚é(” )
		* @param	pos	¶¬À•W
		* @param	aabb	” ‚Ì’e
		* @return	¶¬‚³‚ê‚½’e
		*/
		ShotPtr Create(const Vector3& pos, const ShotAABB& aabb);
		/*
		* @brief	’e‚ğ¶¬‚·‚é(‰ñ“]‚ğl—¶‚µ‚½” )
		* @param	pos	¶¬À•W
		* @param	obb	‰ñ“]‚ğl—¶‚µ‚½” ‚Ì’e
		* @return	¶¬‚³‚ê‚½’e
		*/
		ShotPtr Create(const Vector3& pos, const ShotOBB& obb);

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
			assert(shotArray_[id]);
			return shotArray_[id]; 
		}

		/*
		* @brief	’e‚ğ”‚ğæ“¾‚·‚é
		* @param	’e‚Ì”
		*/
		size_t GetShotCount()
		{
			return shotArray_.size();
		}

	};
}
//ŠÈˆÕƒAƒNƒZƒX—p
#define ShotManagerInstance 	ActionGame::CShotManager::GetInstance()

