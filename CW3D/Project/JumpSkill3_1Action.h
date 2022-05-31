#pragma once

#include	"Action.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		�U���A�N�V����
	 */
	class JumpSkill3_1Action : public Action
	{
	public:
	private:
		//�p�����[�^�[

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		JumpSkill3_1Action()
			: Action()
		{
		}

		/**
		 * @brief		�A�N�V�������̊J�n����
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
		 * @brief		�A�N�V�������̎��s����
		 */
		void Execution() override {
		}

		/**
		 * @brief		����
		 * @param[in]	x		������
		 * @param[in]	z		������
		 */
		void Acceleration(float x, float z) {
			Velocity()->Acceleration(x * (PLAYER_SPEED * PLAYER_WALKSPEED),
				z * (PLAYER_SPEED * PLAYER_WALKSPEED));
		}

		/**
		 * @brief		�A�N�V�������̏I������
		 */
		void End() override {
			Velocity()->SetGravityFlg(true);
		}

		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const ActionKeyType GetKey() const override {
			return STATE_KEY_JUMPSKILL3_1;
		}
	};
	//�|�C���^�u������
	using JumpSkill3_1ActionPtr = std::shared_ptr<JumpSkill3_1Action>;
}
