#pragma once


#include	"AttackBaseState.h"
#include	"EscapeAction.h"


namespace Sample {

	/**
	 * @brief		移動ステート
	 */
	class EscapeState : public AttackBaseState
	{
	public:
		struct Parameter
		{
			//float NextInputFrameTime;
		};
	private:
		Parameter m_Parameter;

		/** 移動アクション */
		EscapeActionPtr			m_EscapeAction;


	public:
		/**
		 * @brief		コンストラクタ
		 */
		EscapeState(Parameter param)
			: AttackBaseState()
			, m_Parameter(param)
		{
		}

		//const EffectCreateParameter& GetCreateEffectStatus() override { return m_Parameter.EffectStatus; }

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {
			m_EscapeAction = Actor()->GetAction<EscapeAction>(GetKey());
			AttackBaseState::Start();

			m_EscapeAction->Start();

			if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) ||
				Input()->IsPress(INPUT_KEY_HORIZONTAL))
			{
				m_EscapeAction->Move(Input()->GetAxis(INPUT_KEY_HORIZONTAL), -(Input()->GetAxis(INPUT_KEY_VERTICAL)));
			}
			else
			{
				if (Actor()->IsReverse())
				{
					m_EscapeAction->Move(1, -(Input()->GetAxis(INPUT_KEY_VERTICAL)));
				}
				else
				{
					m_EscapeAction->Move(-1, - (Input()->GetAxis(INPUT_KEY_VERTICAL)));
				}
			}
		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Execution() override {


			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				if (Actor()->GetTransform()->GetPositionY() > 0)
				{
					ChangeState(STATE_KEY_FALL);
				}
				else
				{
					ChangeState(STATE_KEY_IDLE);
				}
			}
			AttackBaseState::Execution();
		}

		/**
		 * @brief		ステート内の入力処理
		 */
		void InputExecution() override {

			AttackBaseState::InputExecution();
		}



		/**
		 * @brief		ステート内の終了処理
		 */
		void End() override {
			AttackBaseState::End();
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
			return STATE_KEY_ESCAPE;
		}
	};

}