#pragma once


#include	"AttackBaseState.h"
#include	"RunAttack1Action.h"

namespace Sample {

	/**
	 * @brief		移動ステート
	 */
	class RunAttack1State : public AttackBaseState
	{
	private:
		/** 移動アクション */
		RunAttack1ActionPtr			m_RunAttack1Action;

		//1:offset(Vector3) 2:nextHitTime(float) 3:damage(int) 4:knockBack(Vector3)
		//5:collideFlg(bool) 6:type(int) 7:size(Vector3)
		const ShotAABB createShotStatus = { Vector3(0.7f, 0.8f, 0), 0.5f, 0, Vector3(0.4f, 0.0f, 0.0f),false,0, Vector3(1.2f, 1.5f, 0.8f) };

		//1:name(string) 2:offset(Vector3) 3:scale(Vector3) 4:rotate(Vector3)
		//5:speed(float)
		const EffectCreateParameter createEffectStatus = { "Effect2", Vector3(0.8f, 1.0f, 0), Vector3(0.3f, 0.4f, 0.0f), Vector3(0.0f, MOF_ToRadian(360.0f), 0.0f),2.0f };
	public:
		/**
		 * @brief		コンストラクタ
		 */
		RunAttack1State()
			: AttackBaseState()
		{
		}

		const ShotAABB& GetCreateShotStatusAABB() override { return createShotStatus; }
		const EffectCreateParameter& GetCreateEffectStatus() override { return createEffectStatus; }

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {
			m_RunAttack1Action = Actor()->GetAction<RunAttack1Action>(GetKey());

			AttackBaseState::Start();

			m_RunAttack1Action->Start();
			//当たり判定用の弾作成
			CreateShotAABB();
			
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_RUNATTACK1, 0.0f, 1.2f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Execution() override {
			
			for (auto& shot : m_pShots)
			{
				shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
				if (m_FrameTime == 20)
				{
					shot->SetCollideFlg(true);
				}
				else if (shot->GetCollideFlg())
				{
					shot->SetCollideFlg(false);
				}
			}

			if (m_FrameTime == 20)
			{
				CreateEffect();
			}
			m_FrameTime++;
			

			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				ChangeState(STATE_KEY_IDLE);
			}
			/*else if (m_NextInputFlg)
			{
				if (Actor()->GetAnimationState()->GetTime() > 0.7f)
				{
					ChangeState(STATE_KEY_ATTACK2);
				}
			}*/
		}

		/**
		 * @brief		ステート内の入力処理
		 */
		void InputExecution() override {

			if (m_FrameTime > 40)
			{
				if (Input()->IsPush(INPUT_KEY_ATTACK))
				{
					ChangeState(STATE_KEY_ATTACK1);
				}
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
			return STATE_KEY_RUNATTACK1;
		}
	};

}