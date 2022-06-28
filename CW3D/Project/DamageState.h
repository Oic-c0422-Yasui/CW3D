#pragma once

#include	"State.h"
#include	"DamageAction.h"

namespace Sample {

	/**
	 * @brief		ダメージステート
	 */
	class DamageState : public State
	{
	public:
		struct Parameter
		{
			float time;
		};
	private:
		Parameter m_Parameter;
		//ダメージステート
		DamageActionPtr			m_DamageAction;
		//現在時間
		float						m_CurrentTime;

	public:
		/**
		 * @brief		コンストラクタ
		 */
		DamageState(Parameter param)
			: State()
			, m_Parameter(param)
			, m_CurrentTime(0.0f) {
		}

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {
			m_CurrentTime = 0.0f;
			m_DamageAction = Actor()->GetAction<DamageAction>(GetKey());
			m_DamageAction->Start();
			
		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Execution() override {
			m_DamageAction->Execution();

			if (Actor()->GetTransform()->GetPositionY() > 0)
			{
				ChangeState(STATE_KEY_FLYDAMAGE);
			}
			
			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				ChangeState(STATE_KEY_IDLE);
			}
			auto& hp = Actor()->GetParameterMap()->Get<Sample::ReactiveParameter<int>>(PARAMETER_KEY_HP);
			if (hp <= 0)
			{
				ChangeState(STATE_KEY_DEAD);
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
			return STATE_KEY_DAMAGE;
		}
	};
}
