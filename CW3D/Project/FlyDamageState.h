#pragma once

#include	"State.h"
#include	"FlyDamageAction.h"

namespace Sample {

	/**
	 * @brief		ダメージステート
	 */
	class FlyDamageState : public State
	{
	private:
		//ダメージステート
		FlyDamageActionPtr			m_DamageAction;
		//ウェイト
		int						wait;
		//現在時間
		int						currentTime;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		FlyDamageState()
			: State()
			, wait(0)
			, currentTime(0) {
		}

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {
			m_DamageAction = Actor()->GetAction<FlyDamageAction>(GetKey());
			m_DamageAction->Start();
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_FLYDAMAGE, 0.0f, 1.2f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Execution() override {
			m_DamageAction->Execution();
			currentTime++;
			if (Actor()->GetTransform()->GetPositionY() <= 0)
			{
				auto& hp = Actor()->GetParameterMap()->Get<int>(PARAMETER_KEY_HP);
				if (hp <= 0)
				{
					ChangeState(STATE_KEY_DEAD);
				}
				else
				{
					ChangeState(STATE_KEY_DOWN);
				}
				
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
			m_DamageAction->End();
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
			return STATE_KEY_FLYDAMAGE;
		}
	};
}
