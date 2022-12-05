#pragma once

#include	"State.h"
#include	"IdleAction.h"

namespace ActionGame {

	/**
	 * @brief		待機ステート
	 */
	class IdleState : public State
	{
	public:
		struct Parameter
		{
			float idleTime;
		};
	private:
		Parameter m_Parameter;
		/** 移動アクション */
		IdleActionPtr			m_IdleAction;
		float					m_Time;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		IdleState(Parameter param);
			

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