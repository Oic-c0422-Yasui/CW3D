#pragma once

#include	"StateAI.h"
#include	"Player.h"
#include	"Collision.h"
#include	"InputDefine.h"
#include	"ParameterDefine.h"
#include	"ServiceLocator.h"

namespace ActionGame {

	/**
	 * @brief		移動ステート
	 */
	class CMoveStateAI : public CStateAI
	{
	private:
		//見失った時間
		int				currentLostTime;
		bool			isAttack;

		Vector3			attackRange_;
		Vector3			vigilangeRange_;
		int				attackTiming_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		CMoveStateAI(Vector3 vigilangeRange, Vector3 attackRange, int timing);
			

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
		void End() override {
		}
	};
}