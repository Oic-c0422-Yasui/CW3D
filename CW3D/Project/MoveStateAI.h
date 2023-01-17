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
	class MoveStateAI : public StateAI
	{
	private:
		//見失った時間
		int				currentLostTime;
		bool			attackFlg;

		Vector3			m_AttackRange;
		Vector3			m_VigilangeRange;
		int				m_AttackTiming;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		MoveStateAI(Vector3 vigilangeRange , Vector3 attackRange,int timing)
			: StateAI()
			, currentLostTime(0)
			, attackFlg(false)
			, m_AttackRange(attackRange)
			, m_VigilangeRange(vigilangeRange)
			, m_AttackTiming(timing)
		{
		}

		/**
		 * @brief		利用キーの登録
		 */
		void RegisterKey() override {
			Input()->AddKey(INPUT_KEY_HORIZONTAL);
			Input()->AddKey(INPUT_KEY_VERTICAL);
			Input()->AddKey(INPUT_KEY_ATTACK);
		}

		/**
		 * @brief		開始
		 */
		void Start() override {
			currentLostTime = 0;
			attackFlg = false;
		}

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