#pragma once

#include	"Action.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		�U���A�N�V����
	 */
	class RunJumpAttack3Action : public Action
	{
	public:
	private:
		//�p�����[�^�[

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		RunJumpAttack3Action()
			: Action()
		{
		}

		/**
		 * @brief		�A�N�V�������̊J�n����
		 */
		void Start() override {
			auto& vel = Velocity();
			vel->SetVelocityY(PLAYER_JUMPPOWER * 0.7f);
			float rotateY = Transform()->GetRotateY();
			if (Transform()->IsReverse())
			{
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(90), 0.18f);
				Velocity()->SetVelocityX(-0.15f);
			}
			else
			{
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.18f);
				Velocity()->SetVelocityX(0.15f);
			}
		}

		/**
		 * @brief		�A�N�V�������̎��s����
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
		 * @brief		�A�N�V�������̏I������
		 */
		void End() override {
		}

		void Jump()
		{
			Velocity()->SetVelocityY(PLAYER_JUMPPOWER * 0.7f);
		}

		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const ActionKeyType GetKey() const override {
			return STATE_KEY_RUNJUMPATTACK3;
		}
	};
	//�|�C���^�u������
	using RunJumpAttack3ActionPtr = std::shared_ptr<RunJumpAttack3Action>;
}
