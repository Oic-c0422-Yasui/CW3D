#pragma once
#include "MoveAction.h"


namespace ActionGame {

	/**
	 * @brief		移動アクション
	 */
	class CRunJumpAction : public CMoveAction
	{
	public:
		/**
		 * @brief		コンストラクタ
		 */
		CRunJumpAction(BaseParameter baseParam, CMoveAction::Parameter moveParam);
			

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
	using RunJumpActionPtr = std::shared_ptr<CRunJumpAction>;
}

