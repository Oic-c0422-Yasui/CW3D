#pragma once

#include	"State.h"

namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class MoveState : public State
	{
	private:
		/** �ړ��A�N�V���� */
		MoveActionPtr			moveAction_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		MoveState()
			: State() {
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			moveAction_ = Actor()->GetAction<MoveAction>("Move");
			//Actor()->GetAnimationState()->ChangeMotion("Move");
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Exec() override {
		}

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		void InputExec() override {
			//���E�ňړ�
			if (Input()->IsNegativePress("Horizontal"))
			{
				moveAction_->Acceleration(-PLAYER_SPEED, PLAYER_MAXSPEED, true);
			}
			else if (Input()->IsPress("Horizontal"))
			{
				moveAction_->Acceleration(PLAYER_SPEED, PLAYER_MAXSPEED, false);
			}
			else
			{
				if (!moveAction_->IsMove())
				{
					ChangeState("Idle");
				}
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
			return "Move";
		}
	};

}