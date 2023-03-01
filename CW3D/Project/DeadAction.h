#pragma once
#include	"BaseAction.h"


namespace ActionGame {

	/**
	 * @brief		ダメージアクション
	 */
	class CDeadAction : public CBaseAction
	{
	public:
		/**
					 * @brief		攻撃アクションの設定値
					 */
		struct Parameter
		{
			//減速値
			Vector3					decelerate;
			//終了時間
			float					finishTime;
		};
	private:
		//パラメーター
		Parameter					parameter_;

		//現在時間
		float						currentTime_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		CDeadAction(BaseParameter baseParam, Parameter param);
			

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
		 * @brief		ステートキーの取得
		 */
		const ActionKeyType GetKey() const override;
	};
	//ポインタ置き換え
	using DeadActionPtr = std::shared_ptr<CDeadAction>;
}
