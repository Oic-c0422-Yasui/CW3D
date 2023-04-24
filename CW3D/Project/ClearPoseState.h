#pragma once

#include	"BaseState.h"
#include	"ClearPoseAction.h"

namespace ActionGame {

	/**
	 * @brief		ダメージステート
	 */
	class CClearPoseState : public CBaseState
	{
	public:

	private:

		//ダウンステート
		ClearPoseActionPtr			action_;
		//現在時間
		float						currentTime_;

		bool						isAnimStart_;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		CClearPoseState();
			

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
		void InputExecution() override {
		}

		/**
		 * @brief		ステート内の終了処理
		 */
		void End() override;

		/**
		* @brief		ステート内の接触イベント
		* @param[in]	type		当たった相手のタイプ
		* @param[in]	obj			当たった相手のオブジェクト
		*/
		void CollisionEvent(unsigned int type, std::any obj) override;

		/**
		 * @brief		ステートキーの取得
		 */
		const StateKeyType GetKey() const override;
	};
}