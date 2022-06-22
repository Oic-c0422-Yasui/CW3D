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
		/**
					 * @brief		攻撃アクションの設定値
					 */
		struct Parameter
		{
			//アニメーションパラメーター
			AnimParam				anim;
			//減速値
			Vector3					decelerate;
			//終了時間
			float					finishTime;
		};
	private:
		//パラメーター
		Parameter					m_Parameter;

		//現在時間
		float						m_CurrentTime;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		DeadAction(Parameter param)
			: Action()
			, m_Parameter(param)
		{
		}

		/**
		 * @brief		アクション内の開始処理
		 */
		void Start() override {
			AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
				m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);
			auto& knockBack = ParameterMap()->Get<Vector3>(PARAMETER_KEY_KNOCKBACK);
			Velocity()->SetDecelerate(PLAYER_SPEED, PLAYER_SPEED);
			m_CurrentTime = 0;
		}

		/**
		 * @brief		アクション内の実行処理
		 */
		void Execution() override {
			if (AnimationState()->IsEndMotion())
			{
				m_CurrentTime += CUtilities::GetFrameSecond();
				auto& alpha = ParameterMap()->Get<float>(PARAMETER_KEY_ALPHA);
				//3
				alpha = MyUtilities::Timer(1.0f, m_CurrentTime, 0, m_Parameter.finishTime);
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
