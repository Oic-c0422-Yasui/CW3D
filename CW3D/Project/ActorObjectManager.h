#pragma once

#include "ActorObject.h"
#include "Singleton.h"



namespace ActionGame
{

	/*
	* アクターを管理するクラス
	*/
	class CActorObjectManager : public Singleton<CActorObjectManager>
	{
		friend class Singleton<CActorObjectManager>;
	private:

		using ActorMap = std::unordered_map<uint32_t, ActorObjectWeakPtr>;
		using ActorMapPtr = std::shared_ptr<ActorMap>;
		
		using TagMap = std::unordered_map<CHARA_TYPE, ActorMapPtr>;

		TagMap tagMap_;

		CActorObjectManager()
			: Singleton<CActorObjectManager>()
			, tagMap_()
		{
		}
	private:
		/*
		* @brief	タグ内のアクターを追加する
		* @param[out]	list 追加するアクターのリスト
		*/
		void AddActorList(CHARA_TYPE type, ActorObjectWeakListPtr& list);

	public:

		/*
		* @brief	アクターを追加する
		* @param	actor アクターポインタ
		*/
		void Add(const ActorObjectPtr& actor);

		/*
		* @brief	参照の切れたアクターを削除する
		*/
		void Delete();

		/*
		* @brief	アクターを取得する
		* @param	id	アクターの固有ID
		*/
		ActorObjectPtr GetActor(uint32_t id);

		/*
		* @brief	アクターを取得する
		* @param	parentType	キャラタイプ
		* @param	id		アクターの固有ID
		*/
		ActorObjectPtr GetActor(CHARA_TYPE type, uint32_t id) {
			return (*tagMap_[type])[id].lock();
		}

		/*
		* @brief	タグ内のアクターを取得する
		*/
		ActorObjectWeakListPtr GetActors(CHARA_TYPE type);



		/*
		* @brief	敵対しているアクターを取得する（プレイヤーなら敵とボス、敵ならプレイヤーを取得）
		* @return	成功：アクター配列ポインタ
		*			失敗：nullptr
		*/
		ActorObjectWeakListPtr GetHostilityActors(CHARA_TYPE type);

	};
}
//簡易アクセス用
#define ActorObjectManagerInstance 	ActionGame::CActorObjectManager::GetInstance()

