#pragma once

#include	"Action.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		攻撃アクション
	 */
	class JumpSkill3_1Action : public Action
	{
	public:
	private:
		//パラメーター

	public:
		/**
		 * @brief		コンストラクタ
		 */
		JumpSkill3_1Action()
			: Action()
		{
		}

		/**
		 * @brief		アクション内の開始処理
		 */
		void Start() override {
			Velocity()->SetGravityFlg(false);
			auto& vel = Velocity();
			vel->SetMaxVelocity(PLAYER_MAXSPEED * PLAYER_WALKSPEED, PLAYER_MAXSPEED * PLAYER_WALKSPEED);
			vel->SetDecelerate(PLAYER_MAXSPEED * PLAYER_WALKSPEED, PLAYER_MAXSPEED * PLAYER_WALKSPEED);
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
		 * @brief		加速
		 * @param[in]	x		加速量
		 * @param[in]	z		加速量
		 */
		void Acceleration(float x, float z) {
			Velocity()->Acceleration(x * (PLAYER_SPEED * PLAYER_WALKSPEED),
				z * (PLAYER_SPEED * PLAYER_WALKSPEED));
		}

		/**
		 * @brief		アクション内の終了処理
		 */
		void End() override {
			Velocity()->SetGravityFlg(true);
		}

		/**
		 * @brief		ステートキーの取得
		 */
		const ActionKeyType GetKey() const override {
			return STATE_KEY_JUMPSKILL3_1;
		}
	};
	//ポインタ置き換え
	using JumpSkill3_1ActionPtr = std::shared_ptr<JumpSkill3_1Action>;
}
