#pragma once
#include "Action.h"


namespace ActionGame {

	/**
	 * @brief		移動アクション
	 */
	class IdleMotionAction : public CAction
	{
	public:
		/**
		* @brief		攻撃アクションの設定値
		*/
		struct Parameter
		{
			//アニメーションパラメーター
			AnimParam				anim;

			//加速値
			Vector3					velocity;
		};
	private:
		//パラメーター
		Parameter					m_Parameter;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		IdleMotionAction(Parameter param);
			

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
	using IdleMotionActionPtr = std::shared_ptr<IdleMotionAction>;

}
