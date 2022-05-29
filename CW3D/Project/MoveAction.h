#pragma once
#include "Action.h"


namespace Sample {

	/**
	 * @brief		�ړ��A�N�V����
	 */
	class MoveAction : public Action
	{
	private:

		float m_MoveTime;
		float m_CurrentTime;
		/** �ړ��� */
		CVector3 m_Move;

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
		

		/** ���]�t���O */
		bool			m_ReverseFlg;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		MoveAction()
			: Action()
			, m_Move(0,0,0)
			, m_ReverseFlg(false)
			, m_MoveTime(0.0f)
			, m_CurrentTime(0.0f)
			, m_NowDirection(0)
		{
		}

		/**
		 * @brief		�A�N�V�������̊J�n����
		 */
		void Start() override {
			auto& vel = Velocity();
			vel->SetMaxVelocity(PLAYER_MAXSPEED * PLAYER_WALKSPEED, PLAYER_MAXSPEED * PLAYER_WALKSPEED);
				
			vel->SetMaxGravity(GRAVITYMAX);
			vel->SetDecelerate(PLAYER_MAXSPEED * PLAYER_WALKSPEED, PLAYER_MAXSPEED * PLAYER_WALKSPEED);

			float rotateY = Transform()->GetRotateY();
			if (Transform()->IsReverse())
			{
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(90), 0.18f);
				m_NowDirection = DIRECTION_RIGHT;
			}
			else
			{
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.18f);
				m_NowDirection = DIRECTION_LEFT;
			}
		}

		/**
		 * @brief		�A�N�V�������̎��s����
		 */
		void Execution() override {

			auto& velocity = Velocity();
			bool isReverse = Transform()->IsReverse();
			float rotateY = Transform()->GetRotateY();

			if (velocity->GetVelocityX() < 0 && !isReverse)
			{
				Transform()->SetReverse(true);
				
				
			}
			else if (velocity->GetVelocityX() > 0 && isReverse)
			{
				Transform()->SetReverse(false);
				
			}
			if (velocity->GetVelocityX() < 0)
			{
				if (velocity->GetVelocityZ() > 0 && m_NowDirection != DIRECTION_LEFTUP)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(135), 0.15f);
					m_NowDirection = DIRECTION_LEFTUP;
				}
				else if (velocity->GetVelocityZ() < 0 && m_NowDirection != DIRECTION_LEFTDOWN)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(45), 0.15f);
					m_NowDirection = DIRECTION_LEFTDOWN;
				}
				else if(velocity->GetVelocityZ() == 0 && m_NowDirection != DIRECTION_LEFT)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(90), 0.15f);
					m_NowDirection = DIRECTION_LEFT;
				}
			}
			else if (velocity->GetVelocityX() > 0)
			{
				if (velocity->GetVelocityZ() > 0 && m_NowDirection != DIRECTION_RIGHTUP)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(-135), 0.15f);
					m_NowDirection = DIRECTION_RIGHTUP;
				}
				else if (velocity->GetVelocityZ() < 0 && m_NowDirection != DIRECTION_RIGHTDOWN)
				{
					Velocity()->SetRotateY(rotateY, MOF_ToRadian(-45), 0.15f);
					m_NowDirection = DIRECTION_RIGHTDOWN;
				}
				else if (velocity->GetVelocityZ() == 0 && m_NowDirection != DIRECTION_RIGHT)
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
		 * @brief		���x���Z�b�g
		 */
		void Reset() {
			m_Move = Vector3(0, 0, 0);
			m_ReverseFlg = false;
		}

		/**
		 * @brief		�d�͉���
		 * @param[in]	val		������
		 */
		void Gravity(float val) {
			m_Move.y += val;
			if (m_Move.y >= GRAVITYMAX)
			{
				m_Move.y = GRAVITYMAX;
			}
		}

		/**
		 * @brief		����
		 * @param[in]	x		������
		 * @param[in]	z		������
		 */
		void Acceleration(float x, float z) {
			Velocity()->Acceleration(x * (PLAYER_SPEED * PLAYER_WALKSPEED),
				z *(PLAYER_SPEED * PLAYER_WALKSPEED));
		}



		void SetReverseFlg(bool isReverse)
		{
			m_ReverseFlg = isReverse;
		}


		/**
		 * @brief		���x�擾
		 */
		float GetSpeedX() {
			return m_Move.x;
		}

		/**
		 * @brief		���x�擾
		 */
		float GetSpeedY() {
			return m_Move.y;
		}

		/**
		 * @brief		���x�擾
		 */
		 float GetSpeedZ() {
			return m_Move.z;
		}

		/**
		 * @brief		���]�t���O
		 */
		bool IsReverse() const {
			return m_ReverseFlg;
		}

		/**
		 * @brief		�ړ����f
		 *				�ړ����x�����ȉ��Ȃ��~�Ƃ݂Ȃ�
		 */
		bool IsMove() const {
			if (std::abs(m_Move.x) > 0.01f || std::abs(m_Move.z) > 0.01f)
			{
				return true;
			}
			return false;
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

