#pragma once


#include	"AttackBaseState.h"
#include	"RunJumpAttack2Action.h"

namespace Sample {

	/**
	 * @brief		移動ステート
	 */
	class RunJumpAttack2State : public AttackBaseState
	{
	public:
		struct Parameter : public BaseParam
		{
			float NextInputFrameTime;
			ShotAABB ShotStatus;
		};
	private:
		Parameter m_Parameter;
		/** 移動アクション */
		RunJumpAttack2ActionPtr			m_Attack2Action;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		RunJumpAttack2State(Parameter param)
			: AttackBaseState()
			, m_Parameter(param)
		{
		}

		const ShotAABB& GetCreateShotStatusAABB() override { return m_Parameter.ShotStatus; }

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {
			m_Attack2Action = Actor()->GetAction<RunJumpAttack2Action>(GetKey());
			AttackBaseState::Start();
			m_Attack2Action->Start();
			//当たり判定用の弾作成
			CreateShotAABB();
		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Execution() override {


			for (auto& shot : m_pShots)
			{
				shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
			}

			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				ChangeState(STATE_KEY_FALL);
			}
			if (m_NextInputFlg)
			{
				if (m_CurrentTime > m_Parameter.NextInputFrameTime)
				{
					ChangeState(STATE_KEY_RUNJUMPATTACK3);
				}
			}
			AttackBaseState::Execution();
		}

		/**
		 * @brief		ステート内の入力処理
		 */
		void InputExecution() override {

			if (Input()->IsPush(INPUT_KEY_ATTACK))
			{
				m_NextInputFlg = true;
			}

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
			return STATE_KEY_RUNJUMPATTACK2;
		}
	};

}