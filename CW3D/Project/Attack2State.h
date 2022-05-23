#pragma once


#include	"State.h"
#include	"Attack2Action.h"

namespace Sample {

	/**
	 * @brief		移動ステート
	 */
	class Attack2State : public State
	{
	private:
		/** 移動アクション */
		Attack2ActionPtr			m_Attack2Action;
		bool						m_NextInputFlg;
		int							m_ShotId;
		int							m_FrameTime;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		Attack2State()
			: State()
			, m_NextInputFlg(false)
			, m_ShotId(-1)
			, m_FrameTime(0)
		{
		}

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {
			m_Attack2Action = Actor()->GetAction<Attack2Action>(GetKey());
			m_FrameTime = 0;
			m_NextInputFlg = false;
			m_Attack2Action->Start();
			if (Actor()->IsReverse())
			{
				ShotManagerInstance.Create(Actor()->GetPosition() + Vector3(-0.7f, 0.7f, 0), 1.0f, 0, 0);

			}
			else
			{
				ShotManagerInstance.Create(Actor()->GetPosition() + Vector3(0.7f, 0.7f, 0), 1.0f, 0, 0);
			}

			m_ShotId = ShotManagerInstance.GetShotBackId();
			ShotManagerInstance.GetShot(m_ShotId)->SetHide(true);
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_ATTACK2, 0.0f, 1.0f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Execution() override {
			
			if (ShotManagerInstance.GetShot(m_ShotId) != nullptr)
			{
				ShotManagerInstance.GetShot(m_ShotId)->AddPosition(Actor()->GetVelocity()->GetVelocity());
				if (m_FrameTime == 25)
				{
					ShotManagerInstance.GetShot(m_ShotId)->SetHide(false);
				}
				else if (!ShotManagerInstance.GetShot(m_ShotId)->IsHide())
				{
					ShotManagerInstance.GetShot(m_ShotId)->SetHide(true);
				}
			}
			m_FrameTime++;
			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				ChangeState(STATE_KEY_IDLE);
			}
			if (m_NextInputFlg)
			{
				if (Actor()->GetAnimationState()->GetTime() > 0.7f)
				{
					ChangeState(STATE_KEY_ATTACK3);
				}
			}
		}

		/**
		 * @brief		ステート内の入力処理
		 */
		void InputExecution() override {

			if (Input()->IsPush(INPUT_KEY_ATTACK))
			{
				m_NextInputFlg = true;
			}
			
		}



		/**
		 * @brief		ステート内の終了処理
		 */
		void End() override {
			if (m_ShotId > -1)
			{
				ShotManagerInstance.GetShot(m_ShotId)->SetShow(false);
				ShotManagerInstance.Delete();
			}
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
			return STATE_KEY_ATTACK2;
		}
	};

}