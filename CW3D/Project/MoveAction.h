#pragma once
#include "Action.h"


namespace Sample {

	/**
	 * @brief		�ړ��A�N�V����
	 */
	class MoveAction : public Action
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
			Vector3					maxVelocity;

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
		MoveAction(Parameter param)
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
			//PLAYER_MAXSPEED * PLAYER_WALKSPEED
			vel->SetMaxVelocity(m_Parameter.maxVelocity.x, m_Parameter.maxVelocity.z);
			//GRAVITYMAX
			vel->SetMaxGravity(m_Parameter.maxGravity);
			//PLAYER_MAXSPEED * PLAYER_WALKSPEED
			vel->SetDecelerate(m_Parameter.decelerate.x, m_Parameter.decelerate.z);

			float rotateY = Transform()->GetRotateY();
			if (Transform()->IsReverse())
			{
				vel->SetRotateY(rotateY, MOF_ToRadian(90), 0.18f);
				m_NowDirection = DIRECTION_RIGHT;
			}
			else
			{
				vel->SetRotateY(rotateY, MOF_ToRadian(-90), 0.18f);
				m_NowDirection = DIRECTION_LEFT;
			}
		}

		/**
		 * @brief		�A�N�V�������̎��s����
		 */
		void Execution() override {

			auto& vel = Velocity();
			bool isReverse = Transform()->IsReverse();
			float rotateY = Transform()->GetRotateY();

			if (vel->GetVelocityX() < 0 && !isReverse)
			{
				Transform()->SetReverse(true);
				
				
			}
			else if (vel->GetVelocityX() > 0 && isReverse)
			{
				Transform()->SetReverse(false);
				
			}
			if (vel->GetVelocityX() < 0)
			{
				if (vel->GetVelocityZ() > 0 && m_NowDirection != DIRECTION_LEFTUP)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(135), 0.15f);
					m_NowDirection = DIRECTION_LEFTUP;
				}
				else if (vel->GetVelocityZ() < 0 && m_NowDirection != DIRECTION_LEFTDOWN)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(45), 0.15f);
					m_NowDirection = DIRECTION_LEFTDOWN;
				}
				else if(vel->GetVelocityZ() == 0 && m_NowDirection != DIRECTION_LEFT)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(90), 0.15f);
					m_NowDirection = DIRECTION_LEFT;
				}
			}
			else if (vel->GetVelocityX() > 0)
			{
				if (vel->GetVelocityZ() > 0 && m_NowDirection != DIRECTION_RIGHTUP)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(-135), 0.15f);
					m_NowDirection = DIRECTION_RIGHTUP;
				}
				else if (vel->GetVelocityZ() < 0 && m_NowDirection != DIRECTION_RIGHTDOWN)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(-45), 0.15f);
					m_NowDirection = DIRECTION_RIGHTDOWN;
				}
				else if (vel->GetVelocityZ() == 0 && m_NowDirection != DIRECTION_RIGHT)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.15f);
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
			//PLAYER_SPEED * PLAYER_WALKSPEED
			Velocity()->Acceleration(x * m_Parameter.velocity.x,
				z * m_Parameter.velocity.z);
		}



		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const ActionKeyType GetKey() const override {
			return STATE_KEY_MOVE;
		}
	};
	//�|�C���^�u������
	using MoveActionPtr = std::shared_ptr<MoveAction>;

}

