#pragma once


#include "EnemyBuildParameter.h"
#include "Object.h"
#include "IClearTerm.h"
#include "EnemySpawner.h"


namespace ActionGame
{
	/*
	* @brief	ステージを区切るためのクラス
	*/
	class CDivision
	{
	public:
		//区画データ
		struct DIVISION_DATA
		{
			ClearTerm::ClearTermArray	ClearTerms;		//クリア条件
			EnemyBuildParameterArrayPtr EnemysParam;	//敵生成パラメータ
			Spawner::EnemySpawnerArrayPtr EnemySpawners;	//敵スポナー
			size_t EnemyCount;								//生成する敵の数
			std::vector<ObjectPtr> Objects;				//区画オブジェクト
			size_t ObjectCount;							//区画オブジェクトの数

			float width;
		};
	private:
		DIVISION_DATA data_;
		bool isClear_;
	public:
		CDivision(DIVISION_DATA data);
		~CDivision();

		/*
		* @brief	初期化
		*/
		void Initialize();
		/*
		* @brief	更新
		*/
		void Update();
		/*
		* @brief	解放
		*/
		void Release();
		
		/*
		* @brief	敵の生成パラメータ取得
		* @return	敵の生成データ
		*/
		const EnemyBuildParameterArrayPtr& GetEnemysParam()
		{
			return data_.EnemysParam;
		}

		/*
		* @brief	敵のスポナー取得
		* @return	敵のスポナー
		*/
		const Spawner::EnemySpawnerArrayPtr& GetEnemySpawners()
		{
			return data_.EnemySpawners;
		}

		/*
		* @brief	区画オブジェクト取得
		* @param	id 配列番号
		* @return	区画オブジェクト
		*/
		const ObjectPtr& GetObj(size_t id)
		{
			assert(data_.Objects[id]);
			return data_.Objects[id];
		}

		/*
		* @brief	区画オブジェクト数取得
		* @return	区画オブジェクト数
		*/
		size_t GetObjCount() const noexcept
		{
			return data_.ObjectCount;
		}

		/*
		* @brief	生成する敵の数取得
		* @return	生成する敵の数
		*/
		size_t GetEnemyCount() const noexcept
		{
			return data_.EnemyCount;
		}

		/*
		* @brief	区画オブジェクトをすべて破棄する
		*/
		void ClearObject() noexcept
		{
			SetShowObjects(false);
		}

		/*
		* @brief	区画オブジェクトの表示設定
		* @param	isShow 表示可否
		*/
		void SetShowObjects(bool isShow) noexcept
		{
			for (auto& object : data_.Objects)
			{
				object->SetShow(isShow);
			}
		}

		/*
		* @brief	区画をクリアしているか？
		* @param	provider	クリア条件に必要なパラメータを提供するプロバイダ
		* @return	true　ならクリア
		*/
		bool IsClear(const ClearTerm::ProviderPtr& provider);
	};

	using DivisionPtr = std::shared_ptr<CDivision>;
	using DivisionArray = std::vector<DivisionPtr>;
	using DivisionArrayPtr = std::shared_ptr<DivisionArray>;
}


