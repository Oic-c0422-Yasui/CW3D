#pragma once
#include "Action.h"


namespace Sample {

	/**
	 * @brief		�ړ��A�N�V����
	 */
	class RunAction : public Action
	{
	private:

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		RunAction()
			: Action()

		{
		}

		/**
		 * @brief		�A�N�V�������̊J�n����
		 */
		void Start() override {
			auto& vel = Velocity();
			vel->SetMaxVelocity(PLAYER_MAXSPEED, PLAYER_MAXSPEED);

			vel->SetMaxGravity(GRAVITYMAX);
			vel->SetDecelerate(PLAYER_SPEED, PLAYER_SPEED);

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
			//�ړ����Ȃ��ꍇ����

			auto& velocity = Velocity();
			bool isReverse = Transform()->IsReverse();

			if (velocity->GetVelocityX() < 0 && !isReverse)
			{
				float rotateY = Transform()->GetRotateY();
				Transform()->SetReverse(true);
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(90), 0.18f);
			}
			else if (velocity->GetVelocityX() > 0 && isReverse)
			{
				float rotateY = Transform()->GetRotateY();
				Transform()->SetReverse(false);
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.18f);
			}
		
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
			return STATE_KEY_RUN;
		}
	};
	//�|�C���^�u������
	using RunActionPtr = std::shared_ptr<RunAction>;

}

