#pragma once

#include	"Action.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		�U���A�N�V����
	 */
	class JumpAttack1Action : public Action
	{
	public:
	private:
		//�p�����[�^�[

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		JumpAttack1Action()
			: Action()
		{
		}

		/**
		 * @brief		�A�N�V�������̊J�n����
		 */
		void Start() override {

			Velocity()->SetDecelerate(PLAYER_SPEED * 0.3f, PLAYER_SPEED * 0.3f);
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
		 * @brief		�A�N�V�������̏I������
		 */
		void End() override {
		}

		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const ActionKeyType GetKey() const override {
			return STATE_KEY_JUMPATTACK1;
		}
	};
	//�|�C���^�u������
	using JumpAttack1ActionPtr = std::shared_ptr<JumpAttack1Action>;
}
