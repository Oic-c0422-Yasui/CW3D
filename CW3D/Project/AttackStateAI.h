#pragma once

#include	"StateAI.h"
#include	"Player.h"
#include	"Collision.h"
#include	"ServiceLocator.h"

namespace ActionGame {

	/**
	 * @brief		移動ステート
	 */
	class CAttackStateAI : public CStateAI
	{
	private:
		//見失った時間
		int				currentLostTime;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		CAttackStateAI();

		/**
		 * @brief		利用キーの登録
		 */
		void RegisterKey() override;

		/**
		 * @brief		開始
		 */
		void Start() override;

		/**
		 * @brief		更新
		 */
		void Update() override;

		/**
		 * @brief		終了
		 */
		void End() override;
	};
}