#pragma once
#include "Action.h"


namespace Sample {

	/**
	 * @brief		�ړ��A�N�V����
	 */
	class IdleAction : public Action
	{
	private:

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		IdleAction()
			: Action()

		{
		}

		/**
		 * @brief		�A�N�V�������̊J�n����
		 */
		void Start() override {
			auto& vel = Velocity();

			vel->SetDecelerate(PLAYER_SPEED * 0.3f, PLAYER_SPEED * 0.3f);

			float rotateY = Transform()->GetRotateY();
			if (Transform()->IsReverse())
			{
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(90), 0.15f);
			}
			else
			{
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.15f);
			}
		}

		/**
		 * @brief		�A�N�V�������̎��s����
		 */
		void Exection() override {

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
			return STATE_KEY_IDLE;
		}
	};
	//�|�C���^�u������
	using IdleActionPtr = std::shared_ptr<IdleAction>;

}
