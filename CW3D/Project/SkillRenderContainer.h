#pragma once

#include "SkillRender.h"
#include "SkillPresenter.h"
#include "ServiceLocator.h"

#include "SkillUltGaugePresenter.h"
#include "SkillUltGaugeRender.h"
#include "UltimateSkill.h"
#include "AdditionalSkill.h"

namespace ActionGame
{
	//座標呼び出し用関数
	using PositionFunc = std::function<Vector2(const std::string&)>;

	/**
	 * @brief		スキルをまとめて表示する
	 */
	class CSkillRenderContainer
	{
	private:

		std::vector < ActionGame::SkillRenderPtr>	skillRenderArray_;
		std::vector < ActionGame::SkillUltGaugeRenderPtr> ultGaugeRenderArray_;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		CSkillRenderContainer();

		/**
		 * @brief		デストラクタ
		 */
		~CSkillRenderContainer();

		/**
		 * @brief		読み込み
		 */
		bool Load();
		
		/**
		 * @brief		初期化
		 */
		void Initialize(PositionFunc func);

		/**
		 * @brief		描画
		 */
		void Render();

		/*
		* @brief		解放
		*/
		void Release();
	};

	using SkillRenderContainerPtr = std::shared_ptr<CSkillRenderContainer>;
}
