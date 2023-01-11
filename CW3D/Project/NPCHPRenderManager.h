#pragma once
#include "NormalEnemyHPRender.h"
#include "BossHPRender.h"

namespace ActionGame
{
	class NPCHPRenderManager
	{
	private:
		std::vector<NormalEnemyHPRenderPtr> m_NormalHPRender;
		std::vector<BossHPRenderPtr> m_BossHPRender;

	public:
		NPCHPRenderManager();
		~NPCHPRenderManager();
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
		* @brief	HPバーの描画順序入れ替え
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


