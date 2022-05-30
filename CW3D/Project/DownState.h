#pragma once

#include	"State.h"
#include	"DownAction.h"

namespace Sample {

	/**
	 * @brief		ダメージステート
	 */
	class DownState : public State
	{
	private:
		//ダメージステート
		DownActionPtr			m_DownAction;
		//終了時間
		float						m_FinishTime;
		//現在時間
		float						m_CurrentTime;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		DownState()
			: State()
			, m_FinishTime(0)
			, m_CurrentTime(0) {
		}

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {
			m_CurrentTime = 0;
			m_FinishTime = 3;
			auto& invincible = Actor()->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
			invincible = m_FinishTime;
			m_DownAction = Actor()->GetAction<DownAction>(GetKey());
			m_DownAction->Start();
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_DOWN, 0.0f, 1.2f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Execution() override {
			m_DownAction->Execution();
			if (m_CurrentTime < m_FinishTime)
			{
				m_CurrentTime += CUtilities::GetFrameSecond();
			}
			else
			{
				ChangeState(STATE_KEY_IDLE);
			}
		}

		/**
		 * @brief		ステート内の入力処理
		 */
		void InputExecution() override {
		}

		/**
		 * @brief		ステート内の終了処理
		 */
		void End() override {
			m_DownAction->End();
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
			return STATE_KEY_DOWN;
		}
	};
}
