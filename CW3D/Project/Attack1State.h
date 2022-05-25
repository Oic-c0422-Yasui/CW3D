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
		ShotPtr					m_Shot;
		EffectPtr				m_Effect;
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
				m_Shot = ShotManagerInstance.Create(Actor()->GetPosition() + Vector3(-0.8f, 0.7f, 0), 0.8f, 0);
				
			}
			else
			{
				m_Shot = ShotManagerInstance.Create(Actor()->GetPosition() + Vector3(0.8f, 0.7f, 0), 0.8f, 0);
			}

			m_FrameTime = 0;
			m_ShotId = ShotManagerInstance.GetShotBackId();
			

			//EffectManagerInstance.GetManager()->SetRotation(effect->GetHandle(), 0.0f, MOF_ToRadian(90.0f), 0.0f);
			
			m_Shot->SetCollideFlg(false);
			m_Shot->SetKnockBack(0.3f);
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_ATTACK1, 0.0f,1.2f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Execution() override {

			if (m_Shot != nullptr)
			{
				m_Shot->AddPosition(Actor()->GetVelocity()->GetVelocity());
				if (m_FrameTime == 25)
				{
					m_Shot->SetCollideFlg(true);
					m_Effect = EffectControllerInstance.Play("Effect1");

					EffectControllerInstance.SetRotate(m_Effect->GetHandle(), Vector3(0.0f, MOF_ToRadian(90.0f), 0.0f));
					EffectControllerInstance.SetPosition(m_Effect->GetHandle(), Actor()->GetPosition() + Vector3(0.8f, 0.7f, 0));
				}
				else if (m_Shot->GetCollideFlg())
				{
					m_Shot->SetCollideFlg(false);
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
			if (m_Shot != nullptr)
			{
				m_Shot->SetShow(false);
				ShotManagerInstance.Delete();
			}
			if (m_Effect != nullptr)
			{
				m_Effect->SetStop(true);
				EffectControllerInstance.Delete();
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