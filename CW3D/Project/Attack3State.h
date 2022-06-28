#pragma once


#include	"AttackBaseState.h"
#include	"Attack3Action.h"

namespace Sample {

	/**
	 * @brief		移動ステート
	 */
	class Attack3State : public AttackBaseState
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
		Attack3ActionPtr			m_Attack3Action;


		bool collideFirstStartFlg;
		bool collideSecondStartFlg;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		Attack3State(Parameter param)
			: AttackBaseState()
			, m_Parameter(param)
			, collideFirstStartFlg(false)
			, collideSecondStartFlg(false)
		{
		}

		const ShotAABB& GetCreateShotStatusAABB() override { return m_Parameter.ShotStatus; }

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {
			m_Attack3Action = Actor()->GetAction<Attack3Action>(GetKey());

			AttackBaseState::Start();

			m_Attack3Action->Start();
			collideFirstStartFlg = false;
			collideSecondStartFlg = false;
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
				if ((m_CurrentTime >= m_Parameter.CollideFirstStartFrameTime && !collideFirstStartFlg) 
					|| (m_CurrentTime >= m_Parameter.CollideSecondStartFrameTime && !collideSecondStartFlg))
				{
					shot->SetCollideFlg(true);
					if (m_CurrentTime >= m_Parameter.CollideFirstStartFrameTime && !collideFirstStartFlg)
					{
						m_Attack3Action->Execution();
						
					}

				}
				else if (shot->GetCollideFlg())
				{
					shot->SetCollideFlg(false);
				}

			}
			if (m_CurrentTime >= m_Parameter.CollideFirstStartFrameTime && !collideFirstStartFlg)
			{
				collideFirstStartFlg = true;
			}
			if (m_CurrentTime >= m_Parameter.CollideSecondStartFrameTime && !collideSecondStartFlg)
			{
				collideSecondStartFlg = true;
			}
;

			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				ChangeState(STATE_KEY_IDLE);
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
			return STATE_KEY_ATTACK3;
		}
	};

}