#pragma once

#include	"Action.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		攻撃アクション
	 */
	class RunJumpAttack3Action : public Action
	{
	public:
		/**
		* @brief		攻撃アクションの設定値
		*/
		struct Parameter
		{
			//アニメーションパラメーター
			AnimParam				anim;
			//加速値
			Vector3					velocity;
			float					jumpPower;
		};
	private:
		//パラメーター
		Parameter					m_Parameter;
	public:
		/**
		 * @brief		コンストラクタ
		 */
		RunJumpAttack3Action(Parameter param)
			: Action()
			, m_Parameter(param)
		{
		}

		/**
		 * @brief		アクション内の開始処理
		 */
		void Start() override {
			auto& vel = Velocity();
			//JUMPPOWER * 0.7
			vel->SetVelocityY(m_Parameter.jumpPower);
			float rotateY = Transform()->GetRotateY();
			if (Transform()->IsReverse())
			{
				vel->SetRotateY(rotateY, MOF_ToRadian(90), 0.18f);
				//x:0.15
				vel->SetVelocityX(-m_Parameter.velocity.x);
			}
			else
			{
				vel->SetRotateY(rotateY, MOF_ToRadian(-90), 0.18f);
				vel->SetVelocityX(m_Parameter.velocity.x);
			}
		}

		/**
		 * @brief		アクション内の実行処理
		 */
		void Execution() override {
			if (Transform()->IsReverse())
			{
				Velocity()->SetVelocity(Vector3(-0.1f, 0, 0));
			}
			else
			{
				Velocity()->SetVelocity(Vector3(0.1f, 0, 0));
			}
		}

		/**
		 * @brief		アクション内の終了処理
		 */
		void End() override {
		}

		void Jump()
		{
			Velocity()->SetVelocityY(m_Parameter.jumpPower);
		}

		/**
		 * @brief		ステートキーの取得
		 */
		const ActionKeyType GetKey() const override {
			return STATE_KEY_RUNJUMPATTACK3;
		}
	};
	//ポインタ置き換え
	using RunJumpAttack3ActionPtr = std::shared_ptr<RunJumpAttack3Action>;
}
