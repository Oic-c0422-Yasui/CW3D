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
		struct Parameter
		{
			float NextInputFrameTime;
			ShotAABB ShotStatus;
		};
	private:
		Parameter m_Parameter;
		/** 移動アクション */
		RunJumpAttack2ActionPtr			m_Attack2Action;

		const float NextInputFrameTime = GameFrameTime * 20.0f;

		//1:offset(Vector3) 2:nextHitTime(float) 3:damage(int) 4:knockBack(Vector3)
		//5:collideFlg(bool) 6:type(int) 7:size(Vector3)
		ShotAABB createShotStatus = { Vector3(0.7f, 0.7f, 0), 10.0f, 0, Vector3(0.2f, 0.2f, 0.0f),true,CHARA_PLAYER, nullptr, Vector3(1.5f, 1.5f, 1.5f) };
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
			//Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_ATTACK2, 0.0f, 1.5f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
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