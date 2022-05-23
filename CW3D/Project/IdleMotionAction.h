#pragma once
#include "Action.h"


namespace Sample {

	/**
	 * @brief		�ړ��A�N�V����
	 */
	class IdleMotionAction : public Action
	{
	private:

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		IdleMotionAction()
			: Action()

		{
		}

		/**
		 * @brief		�A�N�V�������̊J�n����
		 */
		void Start() override {
			auto& vel = Velocity();

			vel->SetDecelerate(PLAYER_SPEED, PLAYER_SPEED);

			float rotateY = Transform()->GetRotateY();
			if (Transform()->IsReverse())
			{
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(180), 0.2f);
			}
			else
			{
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(0), 0.2f);
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
		 * @brief		����
		 * @param[in]	x		������
		 * @param[in]	z		������
		 */
		void Acceleration(float x, float z) {
			Velocity()->Acceleration(x * PLAYER_SPEED,
				z * PLAYER_SPEED);
		}

		/**
		 * @brief		���x���Z�b�g
		 */
		void Reset() {

		}



		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const ActionKeyType GetKey() const override {
			return STATE_KEY_IDLEMOTION;
		}
	};
	//�|�C���^�u������
	using IdleMotionActionPtr = std::shared_ptr<IdleMotionAction>;

}
