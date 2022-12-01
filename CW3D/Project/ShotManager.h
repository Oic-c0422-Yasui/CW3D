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
		* @brief	弾を生成する(球体)
		* @param	pos	生成座標
		* @param	sphere	球体の弾
		* @return	生成された弾
		*/
		ShotPtr Create(const Vector3& pos, const ShotSphere& sphere);
		/*
		* @brief	弾を生成する(四角)
		* @param	pos	生成座標
		* @param	aabb	四角の弾
		* @return	生成された弾
		*/
		ShotPtr Create(const Vector3& pos, const ShotAABB& aabb);

		/*
		* @brief	非表示の弾を削除する
		*/
		void Delete();

		/*
		* @brief	弾を非表示にする
		*/
		void Reset();

		/*
		* @brief	更新
		*/
		void Update();
		/*
		* @brief	描画
		*/
		void Render();


		/*
		* @brief	弾を取得する
		* @param	id 弾の配列番号
		* @return	弾
		*/
		const ShotPtr& GetShot(size_t id) 
		{
			assert(m_Shots[id]);
			return m_Shots[id]; 
		}

		/*
		* @brief	弾を数を取得する
		* @param	弾の数
		*/
		size_t GetShotCount()
		{
			return m_Shots.size();
		}

	};
}
//簡易アクセス用
#define ShotManagerInstance 	Sample::CShotManager::GetInstance()

