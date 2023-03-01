#pragma once

#include	"StateAI.h"
#include	"Player.h"
#include	"Collision.h"
#include	"Common.h"
#include	"InputDefine.h"
#include	"ServiceLocator.h"

namespace ActionGame {

	/**
	 * @brief		待機ステート
	 */
	class CIdleStateAI : public CStateAI
	{
	private:
		bool			isAttack;

		Vector3			vigilangeRange_;

		Vector3			attackRange_;

		int				attackTiming_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		CIdleStateAI(Vector3 vigilanceRange, Vector3 attackRange, int attackTiming);
			
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
