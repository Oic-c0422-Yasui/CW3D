#pragma once


#include	"State.h"
#include	"Attack1Action.h"

namespace Sample {

	/**
	 * @brief		移動ステート
	 */
	class Attack1State : public State
	{
	private:
		/** 移動アクション */
		Attack1ActionPtr			m_Attack1Action;
		bool					m_NextInputFlg;
		int						m_ShotId;
		int						m_FrameTime;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		Attack1State()
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
			m_Attack1Action = Actor()->GetAction<Attack1Action>(GetKey());

			m_NextInputFlg = false;
			if (Input()->IsPress(INPUT_KEY_HORIZONTAL))
			{
				Actor()->SetReverse(false);
				
			}
			else if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL))
			{
				Actor()->SetReverse(true);
				
			}
			m_Attack1Action->Start();
			if (Actor()->IsReverse())
			{
				ShotManagerInstance.Create(Actor()->GetPosition() + Vector3(-0.8f, 0.7f, 0), 0.8f, 0);
				
			}
			else
			{
				ShotManagerInstance.Create(Actor()->GetPosition() + Vector3(0.8f, 0.7f, 0), 0.8f, 0);
			}
			m_FrameTime = 0;
			m_ShotId = ShotManagerInstance.GetShotBackId();
			EffectPtr effect = EffectControllerInstance.Play("Effect1");
			EffectManagerInstance.GetManager()->SetRotation(effect->GetHandle(), 0.0f, MOF_ToRadian(90.0f), 0.0f);
			
			ShotManagerInstance.GetShot(m_ShotId)->SetCollideFlg(false);
			ShotManagerInstance.GetShot(m_ShotId)->SetKnockBack(0.3f);
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_ATTACK1, 0.0f,1.2f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
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
					ShotManagerInstance.GetShot(m_ShotId)->SetCollideFlg(true);
				}
				else if (ShotManagerInstance.GetShot(m_ShotId)->GetCollideFlg())
				{
					ShotManagerInstance.GetShot(m_ShotId)->SetCollideFlg(false);
				}
			}
			
			m_FrameTime++;

			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				ChangeState(STATE_KEY_IDLE);
			}
			else if (m_NextInputFlg)
			{
				if (Actor()->GetAnimationState()->GetTime() > 0.7f)
				{
					ChangeState(STATE_KEY_ATTACK2);
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
			return STATE_KEY_ATTACK1;
		}
	};

}