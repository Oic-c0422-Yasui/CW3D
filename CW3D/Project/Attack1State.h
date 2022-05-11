#pragma once


#include	"State.h"
#include	"MoveAction.h"
#include	"Attack1Action.h"

namespace Sample {

	/**
	 * @brief		移動ステート
	 */
	class Attack1State : public State
	{
	private:
		/** 移動アクション */
		MoveActionPtr			m_MoveAction;
		bool					m_NextInputFlg;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		Attack1State()
			: State()
			, m_NextInputFlg(false)
		{
		}

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {
			m_MoveAction = Actor()->GetAction<MoveAction>(STATE_KEY_MOVE);
			Actor()->GetAnimationState()->ChangeMotionByName("Attack1", 0.0f,1.0f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Execution() override {
			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				ChangeState(m_NextInputFlg ? STATE_KEY_ATTACK2 : STATE_KEY_IDLE);
			}
		}

		/**
		 * @brief		ステート内の入力処理
		 */
		void InputExecution() override {
			//左右で移動

			if (Input()->IsNegativePress(INPUT_KEY_ATTACK))
			{
				m_MoveAction->AccelerationX(-PLAYER_SPEED, PLAYER_MAXSPEED * PLAYER_WALKSPEED);
			}

			//反転
			if (m_MoveAction->IsReverse())
			{
				m_MoveAction->SetRotateY(MOF_ToRadian(90), 0.2f);
			}
			else
			{
				m_MoveAction->SetRotateY(MOF_ToRadian(-90), 0.2f);
			}
		}



		/**
		 * @brief		ステート内の終了処理
		 */
		void End() override {
		}

		/**
		 * @brief		ステート内の接触イベント
		 * @param[in]	type		当たった相手のタイプ
		 * @param[in]	obj			当たった相手のオブジェクト
		 */
		void CollisionEvent(unsigned int type, std::any obj) override {
		}

		/**
		 * @brief		ステートキーの取得
		 */
		const StateKeyType GetKey() const override {
			return STATE_KEY_ATTACK1;
		}
	};

}