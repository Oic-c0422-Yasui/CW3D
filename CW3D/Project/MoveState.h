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
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		MoveState()
			: State()
		{
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_MoveAction = Actor()->GetAction<MoveAction>(STATE_KEY_MOVE);
			if (Input()->IsPress(INPUT_KEY_HORIZONTAL))
			{
				Actor()->SetReverse(false);
			}
			else if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL))
			{
				Actor()->SetReverse(true);
			}
			m_MoveAction->Start();
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_MOVE, 0.0f, 1.0f, 0.1f, TRUE, MOTIONLOCK_OFF, TRUE);
			
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {
			m_MoveAction->Execution();
		}

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		void InputExecution() override {
			InputDash();
			//���E�ňړ�
			
			if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) ||
				Input()->IsPress(INPUT_KEY_HORIZONTAL) ||
				Input()->IsNegativePress(INPUT_KEY_VERTICAL) ||
				Input()->IsPress(INPUT_KEY_VERTICAL))
			{
				m_MoveAction->Acceleration(Input()->GetAxis(INPUT_KEY_HORIZONTAL), -(Input()->GetAxis(INPUT_KEY_VERTICAL)));
			}
			else
			{
				ChangeState(STATE_KEY_IDLE);
			}

			if (Input()->IsPush(INPUT_KEY_JUMP))
			{
				ChangeState(STATE_KEY_JUMP);
			}


			if (Input()->IsPush(INPUT_KEY_ATTACK))
			{
				ChangeState(STATE_KEY_ATTACK1);
			}

			//�Ή������X�L���̃{�^����������Ă����炻�̃X�L���̃X�e�[�g�Ɉړ�
			for (int i = 0; i < SkillManagerInstance.GetCount(); i++)
			{
				if (!SkillManagerInstance.GetSkill(i)->GetCanUseFlg())
				{
					continue;
				}
				if (Input()->IsPush(SkillManagerInstance.GetSkill(i)->GetButton()))
				{
					ChangeState(SkillManagerInstance.GetSkill(i)->GetName());
					break;
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