#pragma once

#include	"State.h"
#include	"DownAction.h"

namespace Sample {

	/**
	 * @brief		ダメージステート
	 */
	class DownState : public State
	{
	public:
		struct Parameter
		{
			float endTime;
		};
	private:
		Parameter m_Parameter;

		//ダウンステート
		DownActionPtr				m_DownAction;
		//現在時間
		float						m_CurrentTime;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		DownState(Parameter param)
			: State()
			, m_Parameter(param)
			, m_CurrentTime(0) {
		}

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {
			m_CurrentTime = 0;
			auto& invincible = Actor()->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
			invincible = m_Parameter.endTime;
			m_DownAction = Actor()->GetAction<DownAction>(GetKey());
			m_DownAction->Start();
		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Execution() override {
			m_DownAction->Execution();
			//3
			if (m_CurrentTime < m_Parameter.endTime)
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
