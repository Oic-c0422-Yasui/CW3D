#pragma once
#include "Action.h"


namespace Sample {

	/**
	 * @brief		�ړ��A�N�V����
	 */
	class RunFallAction : public Action
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
			Vector3					decelerate;
			//�����l
			Vector3					velocity;
			Vector3					maxVelocty;
			//�d��
			float					gravity;
			float					maxGravity;
		};
	private:
		//�p�����[�^�[
		Parameter					m_Parameter;
		int m_NowDirection;
		enum tag_DIRECTION
		{
			DIRECTION_RIGHT,
			DIRECTION_RIGHTUP,
			DIRECTION_RIGHTDOWN,
			DIRECTION_LEFT,
			DIRECTION_LEFTUP,
			DIRECTION_LEFTDOWN,
		};
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		RunFallAction(Parameter param)
			: Action()
			, m_NowDirection(0)
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

			vel->SetMaxVelocity(PLAYER_MAXSPEED , PLAYER_MAXSPEED );
			//PLAYER_MAXSPEED
			vel->SetMaxVelocity(m_Parameter.maxVelocty.x, m_Parameter.maxVelocty.z);
			//GRAVITYMAX
			vel->SetMaxGravity(m_Parameter.maxGravity);
			//GRAVITY
			vel->SetGravity(m_Parameter.gravity);

			float rotateY = Transform()->GetRotateY();
			if (Transform()->IsReverse())
			{
				vel->SetRotateY(rotateY, MOF_ToRadian(90), 0.18f);
				m_NowDirection = DIRECTION_LEFT;
			}
			else
			{
				vel->SetRotateY(rotateY, MOF_ToRadian(-90), 0.18f);
				m_NowDirection = DIRECTION_RIGHT;
			}
		}

		/**
		 * @brief		�A�N�V�������̎��s����
		 */
		void Execution() override {
			auto& vel = Velocity();
			bool isReverse = Transform()->IsReverse();
			float rotateY = Transform()->GetRotateY();

			if (Transform()->IsReverse())
			{
				if (vel->GetVelocityZ() > 0 && m_NowDirection != DIRECTION_LEFTUP)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(135), 0.1f);
					m_NowDirection = DIRECTION_LEFTUP;
				}
				else if (vel->GetVelocityZ() < 0 && m_NowDirection != DIRECTION_LEFTDOWN)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(45), 0.1f);
					m_NowDirection = DIRECTION_LEFTDOWN;
				}
				else if (vel->GetVelocityZ() == 0 && m_NowDirection != DIRECTION_LEFT)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(90), 0.1f);
					m_NowDirection = DIRECTION_LEFT;
				}
			}
			else
			{
				if (vel->GetVelocityZ() > 0 && m_NowDirection != DIRECTION_RIGHTUP)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(-135), 0.1f);
					m_NowDirection = DIRECTION_RIGHTUP;
				}
				else if (vel->GetVelocityZ() < 0 && m_NowDirection != DIRECTION_RIGHTDOWN)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(-45), 0.1f);
					m_NowDirection = DIRECTION_RIGHTDOWN;
				}
				else if (vel->GetVelocityZ() == 0 && m_NowDirection != DIRECTION_RIGHT)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.1f);
					m_NowDirection = DIRECTION_RIGHT;
				}
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
			return STATE_KEY_RUNFALL;
		}
	};
	//�|�C���^�u������
	using RunFallActionPtr = std::shared_ptr<RunFallAction>;
}

