#pragma once

#include	"Action.h"
#include	"GameDefine.h"

namespace Sample {

	/**
	 * @brief		�U���A�N�V����
	 */
	class Skill1_1Action : public Action
	{
	public:
	private:
		//�p�����[�^�[

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Skill1_1Action()
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
			return STATE_KEY_SKILL1_1;
		}
	};
	//�|�C���^�u������
	using Skill1_1ActionPtr = std::shared_ptr<Skill1_1Action>;
}
