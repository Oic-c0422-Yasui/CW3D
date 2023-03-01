#pragma once

#include	"BaseAction.h"


namespace ActionGame {

	/**
	 * @brief		攻撃アクション
	 */
	class CStormSkillAction : public CBaseAction
	{
	public:
		/**
			 * @brief		攻撃アクションの設定値
			 */
		struct Parameter
		{
			//減速値
			Vector3					decelerate;
			//加速値
			Vector3					velocity;
			//最大加速値
			Vector3					maxVelocity;
		};
	private:
		//パラメーター
		Parameter					parameter_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		CStormSkillAction(BaseParameter baseParam, Parameter param);
			

		/**
		 * @brief		アクション内の開始処理
		 */
		void Start() override;

		/**
		 * @brief		アクション内の実行処理
		 */
		void Execution() override;

		/**
		 * @brief		加速
		 * @param[in]	x		加速量
		 * @param[in]	z		加速量
		 */
		void Acceleration(float x, float z);

		/**
		 * @brief		アクション内の終了処理
		 */
		void End() override;

		/**
		 * @brief		ステートキーの取得
		 */
		const ActionKeyType GetKey() const override;
	};
	//ポインタ置き換え
	using StormSkillActionPtr = std::shared_ptr<CStormSkillAction>;
}
