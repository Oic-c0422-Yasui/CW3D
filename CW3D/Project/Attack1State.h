#pragma once


#include	"State.h"
#include	"MoveAction.h"
#include	"Attack1Action.h"

namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class Attack1State : public State
	{
	private:
		/** �ړ��A�N�V���� */
		MoveActionPtr			m_MoveAction;
		bool					m_NextInputFlg;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Attack1State()
			: State()
			, m_NextInputFlg(false)
		{
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_MoveAction = Actor()->GetAction<MoveAction>(STATE_KEY_MOVE);
			Actor()->GetAnimationState()->ChangeMotionByName("Attack1", 0.0f,1.0f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {
			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				ChangeState(m_NextInputFlg ? STATE_KEY_ATTACK2 : STATE_KEY_IDLE);
			}
		}

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		void InputExecution() override {
			//���E�ňړ�

			if (Input()->IsNegativePress(INPUT_KEY_ATTACK))
			{
				m_MoveAction->AccelerationX(-PLAYER_SPEED, PLAYER_MAXSPEED * PLAYER_WALKSPEED);
			}

			//���]
			if (m_MoveAction->IsReverse())
			{
				m_MoveAction->SetRotateY(MOF_ToRadian(90), 0.2f);
			}
			else
			{
				m_MoveAction->SetRotateY(MOF_ToRadian(-90), 0.2f);
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
			return STATE_KEY_ATTACK1;
		}
	};

}