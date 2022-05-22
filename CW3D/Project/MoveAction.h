#pragma once
#include "Action.h"


namespace Sample {

	/**
	 * @brief		�ړ��A�N�V����
	 */
	class MoveAction : public Action
	{
	private:

		float m_SetRotateFlg;
		float m_TargetY;
		float m_MoveTime;
		float m_StartY;
		float m_CurrentTime;
		/** �ړ��� */
		CVector3 m_Move;

		

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
			, m_TargetY(0.0f)
			, m_MoveTime(0.0f)
			, m_StartY(0.0f)
			, m_CurrentTime(0.0f)
			, m_SetRotateFlg(false)
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
			}
			else
			{
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.18f);
			}
		}

		/**
		 * @brief		�A�N�V�������̎��s����
		 */
		void Exection() override {

			auto& velocity = Velocity();
			bool isReverse = Transform()->IsReverse();
			
			if (velocity->GetVelocityX() < 0 && !isReverse)
			{
				float rotateY = Transform()->GetRotateY();
				Transform()->SetReverse(true);
				Velocity()->SetRotateY(rotateY,MOF_ToRadian(90), 0.1f);
			}
			else if (velocity->GetVelocityX() > 0 && isReverse)
			{
				float rotateY = Transform()->GetRotateY();
				Transform()->SetReverse(false);
				Velocity()->SetRotateY(rotateY, MOF_ToRadian(-90), 0.1f);
			}
			/*if (!m_XMoveFlg)
			{
				DecelerateX(PLAYER_SPEED * 0.5);
			}
			if (!m_ZMoveFlg)
			{
				DecelerateZ(PLAYER_SPEED * 0.5);
			}
			if (m_Move.x > 0 && m_ReverseFlg)
			{
				m_ReverseFlg = false;
				SetRotateY(MOF_ToRadian(-90), 0.2f);

			}
			else if (m_Move.x < 0 && !m_ReverseFlg)
			{
				m_ReverseFlg = true;
				SetRotateY(MOF_ToRadian(90), 0.2f);
			}*/

			/*if (m_CurrentTime > m_MoveTime && m_SetRotateFlg)
			{
				Transform()->SetRotateY(m_TargetY);
				m_SetRotateFlg = false;
			}
			else if (m_SetRotateFlg)
			{

				float rotateY = MyUtilities::RotateTimer(m_StartY, m_CurrentTime, m_TargetY, m_MoveTime);

				Transform()->SetRotateY(rotateY);
				m_CurrentTime += CUtilities::GetFrameSecond();
			}*/


			//�d��
			//Gravity(GRAVITY);
			//���ۂɍ��W���ړ�������
			/*Transform()->MovePosition(m_Move);*/
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

		void SetRotateY(float val,float time) {
			m_TargetY = val;
			m_MoveTime = time;
			m_StartY = Transform()->GetRotateY();
			m_CurrentTime = 0;
			m_SetRotateFlg = true;
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

