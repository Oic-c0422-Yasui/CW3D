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
		BYTE					m_NowHorizontal;
		BYTE					m_NowVertical;
		enum Tag_Direction
		{
			NO_DIRECTION = 0,
			PLUS_DIRECTION,
			MINUS_DIRECTION,
		};
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		MoveState()
			: State()
			, m_NowHorizontal(NO_DIRECTION)
			, m_NowVertical(NO_DIRECTION)
		{
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			moveAction_ = Actor()->GetAction<MoveAction>(STATE_KEY_MOVE);
			Actor()->GetAnimationState()->ChangeMotionByName("Walk",1.0f,TRUE,TRUE);
			m_NowHorizontal = NO_DIRECTION;
			m_NowVertical = NO_DIRECTION;
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
				moveAction_->AccelerationX(-PLAYER_SPEED, PLAYER_MAXSPEED * PLAYER_WALKSPEED);
				if (m_NowHorizontal == MINUS_DIRECTION)
				{
					ChangeState(STATE_KEY_RUN);
				}
				else
				{
					m_NowHorizontal = MINUS_DIRECTION;
				}
				
			}
			else if (Input()->IsPress(INPUT_KEY_HORIZONTAL))
			{
				moveAction_->AccelerationX(PLAYER_SPEED, PLAYER_MAXSPEED * PLAYER_WALKSPEED);
				if (m_NowHorizontal == PLUS_DIRECTION)
				{
					ChangeState(STATE_KEY_RUN);
				}
				else
				{
					m_NowHorizontal = PLUS_DIRECTION;
				}
				
			}
			if (Input()->IsNegativePress(INPUT_KEY_VERTICAL))
			{
				moveAction_->AccelerationZ(PLAYER_SPEED, PLAYER_MAXSPEED * PLAYER_WALKSPEED);
				if (m_NowVertical == PLUS_DIRECTION)
				{
					ChangeState(STATE_KEY_RUN);
				}
				else
				{
					m_NowVertical = PLUS_DIRECTION;
				}
			}
			else if (Input()->IsPress(INPUT_KEY_VERTICAL))
			{
				moveAction_->AccelerationZ(-PLAYER_SPEED, PLAYER_MAXSPEED * PLAYER_WALKSPEED);
				if (m_NowVertical == MINUS_DIRECTION)
				{
					ChangeState(STATE_KEY_RUN);
				}
				else
				{
					m_NowVertical = MINUS_DIRECTION;
				}
			}
			if (moveAction_->IsReverse())
			{
				moveAction_->SetRotateY(MOF_ToRadian(90));
			}
			else
			{
				moveAction_->SetRotateY(MOF_ToRadian(-90));
			}
			if(!Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) && !Input()->IsPress(INPUT_KEY_HORIZONTAL) &&
				!Input()->IsNegativePress(INPUT_KEY_VERTICAL) && !Input()->IsPress(INPUT_KEY_VERTICAL))
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