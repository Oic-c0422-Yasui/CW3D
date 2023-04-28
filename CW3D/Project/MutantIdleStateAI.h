#pragma once


#include	"IdleStateAI.h"

namespace ActionGame {

	/**
	 * @brief		待機ステート
	 */
	class CMutantIdleStateAI : public CIdleStateAI
	{
	private:
		bool isAngry;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		CMutantIdleStateAI(Vector3 vigilanceRange, Vector3 attackRange, int attackTiming);

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
