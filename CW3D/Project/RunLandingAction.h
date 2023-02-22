#pragma once
#include "Action.h"


namespace ActionGame {

	/**
	 * @brief		ダッシュ着地アクション
	 */
	class RunLandingAction : public CAction
	{
	public:
		/**
			 * @brief		攻撃アクションの設定値
			 */
		struct Parameter
		{
			//アニメーションパラメーター
			AnimParam				anim;

		};
	private:
		//パラメーター
		Parameter					m_Parameter;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		RunLandingAction(Parameter param);
			

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
	using RunLandingActionPtr = std::shared_ptr<RunLandingAction>;
}

