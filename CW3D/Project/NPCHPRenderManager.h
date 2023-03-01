#pragma once
#include "NormalEnemyHPRender.h"
#include "BossHPRender.h"

namespace ActionGame
{
	class CNPCHPRenderManager
	{
	private:
		std::vector<NormalEnemyHPRenderPtr> normalHPRender_;
		std::vector<BossHPRenderPtr> bossHPRender_;

	public:
		CNPCHPRenderManager();
		~CNPCHPRenderManager();
		/*
		* @brief	読み込み
		*/
		bool Load();
		/*
		* @brief	初期化
		*/
		void Initialize();
		/*
		* @brief	描画
		*/
		void Render();
		/*
		* @brief	２D描画
		*/
		void Render2D();
		/*
		* @brief	解放
		*/
		void Release();
		/*
		* @brief	リセット
		*/
		void Reset();

		/*
		* @brief	通常HPバーの描画順序入れ替え
		*/
		void Sort();

		/*
		* @brief	HPバーの追加（通常HP）
		*/
		void Add(const NormalEnemyHPRenderPtr& render);
		/*
		* @brief	HPバーの追加（ボスHP）
		*/
		void Add(const BossHPRenderPtr& render);
	};

}


