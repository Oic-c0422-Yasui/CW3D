#pragma once
#include	"Action.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		ダメージアクション
	 */
	class FlyDamageAction : public Action
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
			//重力
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
		FlyDamageAction(Parameter param)
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
			//GRAVITYMAX * 0.4f
			Velocity()->SetMaxGravity(m_Parameter.maxGravity);
			//GRAVITY
			Velocity()->SetGravity(m_Parameter.gravity);
			Transform()->SetThrough(true);
			Velocity()->SetVelocity(knockBack);
			//0.05
			Velocity()->SetDecelerate(m_Parameter.decelerate.x, m_Parameter.decelerate.z);
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
			Transform()->SetThrough(false);
		}



		/**
		 * @brief		ステートキーの取得
		 */
		const ActionKeyType GetKey() const override {
			return STATE_KEY_FLYDAMAGE;
		}
	};
	//ポインタ置き換え
	using FlyDamageActionPtr = std::shared_ptr<FlyDamageAction>;
}
