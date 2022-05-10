#pragma once

#include	"State.h"
#include	"MoveAction.h"

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
			moveAction_ = Actor()->GetAction<MoveAction>(STATE_KEY_MOVE);
			Actor()->GetAnimationState()->ChangeMotionByName("Move",1.0f,TRUE,TRUE);
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
			//���E�ňړ�
			if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL))
			{
				moveAction_->AccelerationX(-PLAYER_SPEED, PLAYER_MAXSPEED);
			}
			else if (Input()->IsPress(INPUT_KEY_HORIZONTAL))
			{
				moveAction_->AccelerationX(PLAYER_SPEED, PLAYER_MAXSPEED);
			}
			if (Input()->IsNegativePress(INPUT_KEY_VERTICAL))
			{
				moveAction_->AccelerationZ(-PLAYER_SPEED, PLAYER_MAXSPEED);
				ChangeState(STATE_KEY_MOVE);
			}
			else if (Input()->IsPress(INPUT_KEY_VERTICAL))
			{
				moveAction_->AccelerationZ(PLAYER_SPEED, PLAYER_MAXSPEED);
				ChangeState(STATE_KEY_MOVE);
			}
			if(moveAction_->GetSpeedX() != 0.0f && moveAction_->GetSpeedZ() != 0.0f)
			{
				if (!moveAction_->IsMove())
				{
					ChangeState(STATE_KEY_IDLE);
				}
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
			return STATE_KEY_MOVE;
		}
	};

}