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
		MoveActionPtr			m_MoveAction;
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
			m_MoveAction = Actor()->GetAction<MoveAction>(STATE_KEY_MOVE);
			Actor()->GetAnimationState()->ChangeMotionByName("Walk",1.0f,TRUE,TRUE);
			m_NowHorizontal = NO_DIRECTION;
			m_NowVertical = NO_DIRECTION;
			m_MoveAction->Start();
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
			InputDash();
			//���E�ňړ�
			
			if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL))
			{
				m_MoveAction->AccelerationX(-PLAYER_SPEED, PLAYER_MAXSPEED * PLAYER_WALKSPEED);
				
				
			}
			else if (Input()->IsPress(INPUT_KEY_HORIZONTAL))
			{
				m_MoveAction->AccelerationX(PLAYER_SPEED, PLAYER_MAXSPEED * PLAYER_WALKSPEED);
				
			}
			if (Input()->IsNegativePress(INPUT_KEY_VERTICAL))
			{
				m_MoveAction->AccelerationZ(PLAYER_SPEED, PLAYER_MAXSPEED * PLAYER_WALKSPEED);

			}
			else if (Input()->IsPress(INPUT_KEY_VERTICAL))
			{
				m_MoveAction->AccelerationZ(-PLAYER_SPEED, PLAYER_MAXSPEED * PLAYER_WALKSPEED);

			}

			

			if(!Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) && !Input()->IsPress(INPUT_KEY_HORIZONTAL) &&
				!Input()->IsNegativePress(INPUT_KEY_VERTICAL) && !Input()->IsPress(INPUT_KEY_VERTICAL))
			{
				if (!m_MoveAction->IsMove())
				{
					ChangeState(STATE_KEY_IDLE);
				}
			}
		}

		void InputDash()
		{
			if (Input()->IsNegativeDoublePush(INPUT_KEY_HORIZONTAL) || Input()->IsDoublePush(INPUT_KEY_HORIZONTAL) || 
				Input()->IsNegativeDoublePush(INPUT_KEY_VERTICAL) || Input()->IsDoublePush(INPUT_KEY_VERTICAL))
			{
					ChangeState(STATE_KEY_RUN);
					return;
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