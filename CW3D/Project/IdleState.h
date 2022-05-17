#pragma once

#include	"State.h"
#include	"MoveAction.h"

namespace Sample {

	/**
	 * @brief		�ҋ@�X�e�[�g
	 */
	class IdleState : public State
	{
	private:
		/** �ړ��A�N�V���� */
		MoveActionPtr			m_MoveAction;
		float					m_Time;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		IdleState()
			: State()
			, m_Time(0.0f)
		{
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_MoveAction = Actor()->GetAction<MoveAction>(STATE_KEY_MOVE);
			m_Time = 0.0f;
			if (m_MoveAction->IsReverse())
			{
				m_MoveAction->SetRotateY(MOF_ToRadian(90), 0.15f);
			}
			else
			{
				m_MoveAction->SetRotateY(MOF_ToRadian(-90), 0.15f);

			}
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_IDLE, 0.0f, 1.0f, 0.15f, TRUE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {
			if (m_Time < 5.0f)
			{
				m_Time += CUtilities::GetFrameSecond();
			}
			else
			{
				ChangeState(STATE_KEY_IDLEMOTION);
				
			}
		}

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		void InputExecution() override {
			if (Input()->IsNegativeDoublePush(INPUT_KEY_HORIZONTAL) || Input()->IsDoublePush(INPUT_KEY_HORIZONTAL) ||
				Input()->IsNegativeDoublePush(INPUT_KEY_VERTICAL) || Input()->IsDoublePush(INPUT_KEY_VERTICAL))
			{
				ChangeState(STATE_KEY_RUN);
				return;
			}
			//�L�[�{�[�h�ł̈ړ�
			else if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL))
			{
				m_MoveAction->AccelerationX(-PLAYER_SPEED, PLAYER_MAXSPEED);
				ChangeState(STATE_KEY_MOVE);
			}
			else if (Input()->IsPress(INPUT_KEY_HORIZONTAL))
			{
				m_MoveAction->AccelerationX(PLAYER_SPEED, PLAYER_MAXSPEED);
				ChangeState(STATE_KEY_MOVE);
			}
			if (Input()->IsNegativePress(INPUT_KEY_VERTICAL))
			{
				m_MoveAction->AccelerationZ(PLAYER_SPEED, PLAYER_MAXSPEED);
				ChangeState(STATE_KEY_MOVE);
			}
			else if (Input()->IsPress(INPUT_KEY_VERTICAL))
			{
				m_MoveAction->AccelerationZ(-PLAYER_SPEED, PLAYER_MAXSPEED);
				ChangeState(STATE_KEY_MOVE);
			}

			if (Input()->IsPush(INPUT_KEY_ATTACK))
			{
				ChangeState(STATE_KEY_ATTACK1);
			}

			//�{�^�����ƂɃX�L�����ς��ꍇ
			/*if (Input()->IsPush(INPUT_KEY_ATTACK))
			{
				ChangeState(setting.skill1SetName);
			}*/
		}

		/**
		 * @brief		�X�e�[�g���̏I������
		 */
		void End() override {
		}

		/**
		 * @brief		�X�e�[�g���̐ڐG�C�x���g
		 * @param[in]	type		������������̃^�C�v
		 * @param[in]	obj			������������̃I�u�W�F�N�g
		 */
		void CollisionEvent(unsigned int type, std::any obj) override {
		}

		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const StateKeyType GetKey() const override {
			return STATE_KEY_IDLE;
		}
	};

}