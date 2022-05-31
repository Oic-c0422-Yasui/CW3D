#pragma once
#include	"Action.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		ダメージアクション
	 */
	class DeadAction : public Action
	{
	public:
		//終了時間
		float						m_FinishTime;
		//現在時間
		float						m_CurrentTime;
	private:

	public:
		/**
		 * @brief		コンストラクタ
		 */
		DeadAction()
			: Action()
		{
		}

		/**
		 * @brief		アクション内の開始処理
		 */
		void Start() override {
			auto& knockBack = ParameterMap()->Get<Vector3>(PARAMETER_KEY_KNOCKBACK);
			Velocity()->SetDecelerate(PLAYER_SPEED, PLAYER_SPEED);
			m_CurrentTime = 0;
			m_FinishTime = 3;
		}

		/**
		 * @brief		アクション内の実行処理
		 */
		void Execution() override {
			if (AnimationState()->IsEndMotion())
			{
				m_CurrentTime += CUtilities::GetFrameSecond();
				auto& alpha = ParameterMap()->Get<float>(PARAMETER_KEY_ALPHA);

				alpha = MyUtilities::Timer(1.0f, m_CurrentTime, 0, m_FinishTime);
			}
		}

		/**
		 * @brief		アクション内の終了処理
		 */
		void End() override {
		}



		/**
		 * @brief		ステートキーの取得
		 */
		const ActionKeyType GetKey() const override {
			return STATE_KEY_DEAD;
		}
	};
	//ポインタ置き換え
	using DeadActionPtr = std::shared_ptr<DeadAction>;
}
