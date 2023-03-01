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
		* @brief	弾を生成する(球体)
		* @param	pos	生成座標
		* @param	sphere	球体の弾
		* @return	生成された弾
		*/
		ShotPtr Create(const Vector3& pos, const ShotSphere& sphere);
		/*
		* @brief	弾を生成する(箱)
		* @param	pos	生成座標
		* @param	aabb	箱の弾
		* @return	生成された弾
		*/
		ShotPtr Create(const Vector3& pos, const ShotAABB& aabb);
		/*
		* @brief	弾を生成する(回転を考慮した箱)
		* @param	pos	生成座標
		* @param	obb	回転を考慮した箱の弾
		* @return	生成された弾
		*/
		ShotPtr Create(const Vector3& pos, const ShotOBB& obb);

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
			assert(shotArray_[id]);
			return shotArray_[id]; 
		}

		/*
		* @brief	弾を数を取得する
		* @param	弾の数
		*/
		size_t GetShotCount()
		{
			return shotArray_.size();
		}

	};
}
//簡易アクセス用
#define ShotManagerInstance 	ActionGame::CShotManager::GetInstance()

