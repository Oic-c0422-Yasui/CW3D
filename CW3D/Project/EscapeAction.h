#pragma once

#include	"Action.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		攻撃アクション
	 */
	class EscapeAction : public Action
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
			//加速値
			Vector3					velocity;
		};
	private:
		//パラメーター
		Parameter					m_Parameter;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		EscapeAction(Parameter param)
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
			Velocity()->SetDecelerate(m_Parameter.decelerate.x, m_Parameter.decelerate.z);
			float rotateY = Transform()->GetRotateY();
			if (Transform()->IsReverse())
			{
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(90), 0.18f);
			}
			else
			{
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.18f);
			}
		}

		/**
		 * @brief		アクション内の実行処理
		 */
		void Execution() override {
		}

		/**
		 * @brief		アクション内の終了処理
		 */
		void End() override {
		}

		/**
		 * @brief		加速
		 * @param[in]	x		加速量
		 * @param[in]	z		加速量
		 */
		void Move(float x, float z) {
			Velocity()->SetVelocityX(x * m_Parameter.velocity.x);
			Velocity()->SetVelocityZ(z * m_Parameter.velocity.z);
		}

		/**
		 * @brief		ステートキーの取得
		 */
		const ActionKeyType GetKey() const override {
			return STATE_KEY_ESCAPE;
		}
	};
	//ポインタ置き換え
	using EscapeActionPtr = std::shared_ptr<EscapeAction>;
}
