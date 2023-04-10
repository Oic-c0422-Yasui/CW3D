#pragma once
#include "Enemy.h"

namespace ActionGame
{
	/*
	* @brief	敵マネージャー
	*/
	class CEnemyManager
	{
	private:
		EnemyArrayPtr enemyArray_;
		ActionGame::CReactiveParameter<size_t> enemyCount_;
		ActionGame::CReactiveParameter<size_t> bossCount_;
		ActionGame::CReactiveParameter<size_t> showEnemyCount_;
		size_t enemyMaxCount_;
		size_t bossMaxCount_;
	public:
		CEnemyManager();
		~CEnemyManager();

		/*
		* @brief　初期化
		*/
		void Initialize();
		/*
		* @brief	更新
		*/
		void Update();
		/*
		* @brief	描画
		*/
		void Render();
		/*
		* @brief	デバッグ描画
		*/
		void RenderDebug();
		/*
		* @brief	解放
		*/
		void Release();

		/*
		* @brief	敵の数取得
		*/
		size_t GetEnemyCount() const noexcept
		{
			return enemyCount_;
		}
		/*
		* @brief	敵の最大数取得
		*/
		size_t GetEnemyMaxCount() const noexcept
		{
			return enemyMaxCount_;
		}
		/*
		* @brief	敵の表示数取得
		*/
		size_t GetShowEnemyCount() const noexcept
		{
			return showEnemyCount_;
		}
		/*
		* @brief	ボスの数取得
		*/
		size_t GetBossCount() const noexcept
		{
			return bossCount_;
		}
		/*
		* @brief	ボスの最大数取得
		*/
		size_t GetBossMaxCount() const noexcept
		{
			return bossMaxCount_;
		}


		/*
		* @brief	敵の数通知
		*/
		ActionGame::IObservable<size_t>& GetEnemyCountSubject()
		{
			return enemyCount_;
		}
		/*
		* @brief	敵の表示数通知
		*/
		ActionGame::IObservable<size_t>& GetEnemyShowCountSubject()
		{
			return showEnemyCount_;
		}
		/*
		* @brief	ボスの数通知
		*/
		ActionGame::IObservable<size_t>& GetBossCountSubject()
		{
			return bossCount_;
		}

		/*
		* @brief	敵取得
		* @param	num 敵の配列番号
		*/
		const EnemyPtr& GetEnemy(size_t num)
		{
			assert(enemyArray_->at(num));
			return enemyArray_->at(num);
		}

		/*
		* @brief	敵追加
		* @param	敵のポインタ
		*/
		void AddEnemy(const EnemyPtr& enemy);

		/*
		* @brief	敵配列リセット
		*/
		void ClearEnemyArray();
	};
}

