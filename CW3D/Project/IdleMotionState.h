#pragma once

#include	"State.h"
#include	"MoveAction.h"

namespace Sample {

	/**
	 * @brief		�ҋ@���[�V�����X�e�[�g
	 */
	class IdleMotionState : public State
	{
	private:
		/** �ړ��A�N�V���� */
		MoveActionPtr			m_MoveAction;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		IdleMotionState()
			: State()
		{
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_MoveAction = Actor()->GetAction<MoveAction>(STATE_KEY_MOVE);
			if (m_MoveAction->IsReverse())
			{
				m_MoveAction->SetRotateY(MOF_ToRadian(180));
			}
			else
			{
				m_MoveAction->SetRotateY(0);

			}
			Actor()->GetAnimationState()->ChangeMotionByName("Idle", 1.0f, FALSE, TRUE);
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {
			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				ChangeState(STATE_KEY_IDLE);
			}
		}

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		void InputExecution() override {
			//�L�[�{�[�h�ł̈ړ�
			if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL))
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
			return STATE_KEY_IDLEMOTION;
		}
	};

}