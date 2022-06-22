#pragma once
#include "Action.h"


namespace Sample {

	/**
	 * @brief		�ړ��A�N�V����
	 */
	class JumpAction : public Action
	{
	public:
		/**
		* @brief		�U���A�N�V�����̐ݒ�l
		*/
		struct Parameter
		{
			//�A�j���[�V�����p�����[�^�[
			AnimParam				anim;


			//�����l
			Vector3					velocity;
			Vector3					maxVelocity;

			float					gravity;
			float					maxGravity;
			float					jumpPower;
		};
	private:
		//�p�����[�^�[
		Parameter					m_Parameter;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		JumpAction(Parameter param)
			: Action()
			, m_Parameter(param)
		{
		}

		/**
		 * @brief		�A�N�V�������̊J�n����
		 */
		void Start() override {

			AnimationState()->ChangeMotionByName(m_Parameter.anim.name, m_Parameter.anim.startTime, m_Parameter.anim.speed,
				m_Parameter.anim.tTime, m_Parameter.anim.loopFlg, MOTIONLOCK_OFF, TRUE);
			auto& vel = Velocity();

			//PLAYER_MAXSPEED * PLAYER_WALKSPEED
			vel->SetMaxVelocity(m_Parameter.maxVelocity.x, m_Parameter.maxVelocity.z);
			//GRAVITYMAX
			vel->SetMaxGravity(m_Parameter.maxGravity);
			//PLAYER_JUMPPOWER
			vel->SetVelocityY(m_Parameter.jumpPower);
			//GRAVITY
			vel->SetGravity(m_Parameter.gravity);

			float rotateY = Transform()->GetRotateY();
			if (Transform()->IsReverse())
			{
				vel->SetRotateY(rotateY, MOF_ToRadian(90), 0.18f);
			}
			else
			{
				vel->SetRotateY(rotateY, MOF_ToRadian(-90), 0.18f);
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
			Velocity()->Acceleration(x * m_Parameter.velocity.x,
				z * m_Parameter.velocity.z);
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
			return STATE_KEY_JUMP;
		}
	};
	//�|�C���^�u������
	using JumpActionPtr = std::shared_ptr<JumpAction>;
}

