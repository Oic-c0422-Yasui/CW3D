#pragma once
#include "MoveAction.h"


namespace ActionGame {

	/**
	 * @brief		移動アクション
	 */
	class CRunAction : public CMoveAction
	{
	public:
		/**
		 * @brief		コンストラクタ
		 */
		CRunAction(BaseParameter baseParam, Parameter param);
			
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
		 * @brief		速度リセット
		 */
		void Reset();

		/**
		 * @brief		ステートキーの取得
		 */
		const ActionKeyType GetKey() const override;
	};
	//ポインタ置き換え
	using RunActionPtr = std::shared_ptr<CRunAction>;

}

