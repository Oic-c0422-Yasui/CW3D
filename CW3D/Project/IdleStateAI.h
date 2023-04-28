#pragma once

#include	"BaseStateAI.h"
#include	"Player.h"
#include	"Collision.h"
#include	"Common.h"
#include	"InputDefine.h"
#include	"ServiceLocator.h"

namespace ActionGame {

	/**
	 * @brief		待機ステート
	 */
	class CIdleStateAI : public CBaseStateAI
	{
	protected:
		bool			isAttack_;

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
		virtual void RegisterKey() override;

		/**
		 * @brief		開始
		 */
		virtual void Start() override;

		/**
		 * @brief		更新
		 */
		virtual void Update() override;

		/**
		 * @brief		終了
		 */
		virtual void End() override;
	};
}
