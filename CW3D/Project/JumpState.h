#pragma once

#include	"BaseState.h"
#include	"JumpAction.h"

namespace ActionGame {

	/**
	 * @brief		移動ステート
	 */
	class CJumpState : public CBaseState
	{
	private:
		/** 移動アクション */
		JumpActionPtr			action_;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		CJumpState();
			

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override;

		/**
		 * @brief		ステート内の実行処理
		 */
		void Execution() override;

		/**
		 * @brief		ステート内の入力処理
		 */
		void InputExecution() override;


		/**
		 * @brief		ステート内の終了処理
		 */
		void End() override;



		/**
		 * @brief		ステート内の接触イベント
		 * @param[in]	parentType		当たった相手のタイプ
		 * @param[in]	obj			当たった相手のオブジェクト
		 */
		void CollisionEvent(unsigned int type, std::any obj) override;

		/**
		 * @brief		ステートキーの取得
		 */
		const StateKeyType GetKey() const override;
	};

}