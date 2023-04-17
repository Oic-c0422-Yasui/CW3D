#pragma once

#include "PlayerHPRender.h"
#include "SkillInfoRender.h"
#include "SkillRenderContainer.h"
#include "UltimateGaugeRender.h"
#include "UltGaugePresenter.h"
#include "ComboPresenter.h"

namespace ActionGame
{
	/**
	 * @brief		プレイヤーUI
	 */
	class CPlayerUIRender
	{
	private:
		//HP描画
		PlayerHPRenderPtr			HPRender_;
		//スキル情報描画
		SkillInfoRenderPtr			skillInfoRender_;
		//スキル画像描画
		SkillRenderContainerPtr		skillsRender_;
		UltimateGaugeUIRenderPtr	UltGaugeRender_;
		//コンボ描画
		ComboRenderPtr				comboRender_;
		
		//表示フラグ
		bool						isShow_;

	private:
		/* プライベート関数　*/
		//UI表示
		void VisibleUI();
		//UI非表示
		void DisableUI();
		//キーボードUI表示
		void ChangeKeyBoardUI();
		//コントローラーUI表示
		void ChangeControllerUI();
	public:
		/**
		 * @brief		コンストラクタ
		 */
		CPlayerUIRender();

		/**
		 * @brief		デストラクタ
		 */
		~CPlayerUIRender();

		/*
		* @brief	読み込み
		* @param	player　プレイヤー
		* @param	device	操作デバイス
		* @return	true　なら成功
		*/
		bool Load(const PlayerPtr& player, GameDevice device);

		/*
		* @brief	初期化
		*/
		void Initialize();

		/**
		 * @brief		UI描画
		 */
		void Render();

		/**
		 * @brief		解放
		 */
		void Release();

	};

	using PlayerUIRenderPtr = std::shared_ptr<CPlayerUIRender>;
}
