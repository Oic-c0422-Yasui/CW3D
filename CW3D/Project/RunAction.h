#pragma once
#include "Action.h"


namespace ActionGame {

	/**
	 * @brief		移動アクション
	 */
	class RunAction : public Action
	{
	public:
		/**
		* @brief		攻撃アクションの設定値
		*/
		struct Parameter
		{
			//アニメーションパラメーター
			AnimParam				anim;

			//減速値
			Vector3					decelerate;
			//加速値
			Vector3					velocity;
			Vector3					maxVelocity;

			float					maxGravity;
		};
	private:
		//パラメーター
		Parameter					m_Parameter;
		int m_NowDirection;
		enum tag_DIRECTION
		{
			DIRECTION_RIGHT,
			DIRECTION_RIGHTUP,
			DIRECTION_RIGHTDOWN,
			DIRECTION_LEFT,
			DIRECTION_LEFTUP,
			DIRECTION_LEFTDOWN,
		};
	public:
		/**
		 * @brief		コンストラクタ
		 */
		RunAction(Parameter param);
			

		/**
		 * @brief		アクション内の開始処理
		 */
		void Start() override;

		/**
		 * @brief		アクション内の実行処理
		 */
		void Execution() override;

		/**
		 * @brief		アクション内の終了処理
		 */
		void End() override;

		/**
		 * @brief		加速
		 * @param[in]	x		加速量
		 * @param[in]	z		加速量
		 */
		void Acceleration(float x, float z);

		/**
		 * @brief		速度リセット
		 */
		void Reset();



		/**
		 * @brief		ステートキーの取得
		 */
		const ActionKeyType GetKey() const override;
	};
	//ポインタ置き換え
	using RunActionPtr = std::shared_ptr<RunAction>;

}

