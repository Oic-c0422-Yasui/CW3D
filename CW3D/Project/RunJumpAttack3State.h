#pragma once


#include	"AttackBaseState.h"
#include	"RunJumpAttack3Action.h"

namespace Sample {

	/**
	 * @brief		移動ステート
	 */
	class RunJumpAttack3State : public AttackBaseState
	{
	public:
		struct Parameter : public BaseParam
		{
			float CollideFirstStartFrameTime;
			float CollideSecondStartFrameTime;
			ShotAABB ShotStatus;
		};
	private:
		Parameter m_Parameter;
		/** 移動アクション */
		RunJumpAttack3ActionPtr			m_Attack3Action;


		bool collideStartFlg;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		RunJumpAttack3State(Parameter param)
			: AttackBaseState()
			, m_Parameter(param)
			, collideStartFlg(false)
		{
		}

		const ShotAABB& GetCreateShotStatusAABB() override { return m_Parameter.ShotStatus; }

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {
			m_Attack3Action = Actor()->GetAction<RunJumpAttack3Action>(GetKey());
			AttackBaseState::Start();
			collideStartFlg = false;
			m_Attack3Action->Start();
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
				if (m_CurrentTime >= m_Parameter.CollideFirstStartFrameTime && !collideStartFlg)
				{
						m_Attack3Action->Execution();
						m_Attack3Action->Jump();

				}
				else if (m_CurrentTime >= m_Parameter.CollideSecondStartFrameTime && shot->GetCollideFlg())
				{
					shot->SetCollideFlg(false);
				}

			}
			if (m_CurrentTime >= m_Parameter.CollideFirstStartFrameTime && !collideStartFlg)
			{
				collideStartFlg = true;
			}

			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				ChangeState(STATE_KEY_FALL);
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
			return STATE_KEY_RUNJUMPATTACK3;
		}
	};

}