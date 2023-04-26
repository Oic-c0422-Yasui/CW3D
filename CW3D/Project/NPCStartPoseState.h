#pragma once
#include "BaseState.h"
#include "NPCStartPoseAction.h"

namespace ActionGame
{
    /*
    * @brief	NPC開始ポーズステート
    */
    class CNPCStartPoseState : public CBaseState
    {
	private:

		//開始ポーズステート
		NPCStartPoseActionPtr			action_;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		CNPCStartPoseState();

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


