#pragma once

#include	"Action.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		攻撃アクション
	 */
	class ClearPoseAction : public Action
	{
	public:
		/**
			 * @brief		攻撃アクションの設定値
			 */
		struct Parameter
		{
			//アニメーションパラメーター
			AnimParam				anim;
			AnimParam				fallAnim;
			//減速値
			Vector3					decelerate;
			float					gravity;
			float					maxGravity;
		};
	private:
		//パラメーター
		Parameter					m_Parameter;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		ClearPoseAction(Parameter param)
			: Action()
			, m_Parameter(param)
		{
		}

		/**
		 * @brief		アクション内の開始処理
		 */
		void Start() override {
			if (Transform()->GetPositionY() > 0.0f)
			{
				AnimationState()->ChangeMotionByName(m_Parameter.fallAnim.name, m_Parameter.fallAnim.startTime, m_Parameter.fallAnim.speed,
					m_Parameter.fallAnim.tTime, m_Parameter.fallAnim.loopFlg, MOTIONLOCK_OFF, TRUE);
			}
			else
			{
				StartAnim();
			}

			Velocity()->SetDecelerate(m_Parameter.decelerate.x, m_Parameter.decelerate.z);
			float rotateY = Transform()->GetRotateY();

			Velocity()->SetRotateY(rotateY, MOF_ToRadian(0), 0.18f);
			Velocity()->SetGravity(m_Parameter.gravity);
			Velocity()->SetMaxGravity(m_Parameter.maxGravity);
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

		void StartAnim()
		{
			AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
				m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		ステートキーの取得
		 */
		const ActionKeyType GetKey() const override {
			return STATE_KEY_CLEARPOSE;
		}
	};
	//ポインタ置き換え
	using ClearPoseActionPtr = std::shared_ptr<ClearPoseAction>;
}
