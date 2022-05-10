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
		MoveActionPtr			moveAction_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		IdleState()
			: State() {
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			moveAction_ = Actor()->GetAction<MoveAction>("Move");
			//Actor()->GetAnimationState()->ChangeMotion("Wait");
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {
		}

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		void InputExecution() override {
			//�L�[�{�[�h�ł̈ړ�
			if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL))
			{
				moveAction_->Acceleration(-PLAYER_SPEED, PLAYER_MAXSPEED, true);
				ChangeState(STATE_KEY_MOVE);
			}
			else if (Input()->IsPress(INPUT_KEY_HORIZONTAL))
			{
				moveAction_->Acceleration(PLAYER_SPEED, PLAYER_MAXSPEED, false);
				ChangeState(STATE_KEY_MOVE);
			}
			//��L�[�ŃW�����v
			if (Input()->IsPress("Jump"))
			{
				ChangeState("Jump");
			}
			//SPACE�L�[�ōU��
			if (Input()->IsPush("Attack"))
			{
				ChangeState("Attack");
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
		void CollisionEvent(unsigned int type, anytype obj) override {
		}

		/**
		 * @brief		�X�e�[�g�L�[�̎擾
		 */
		const StateKeyType GetKey() const override {
			return "Idle";
		}
	};

}