#pragma once

#include	"State.h"
#include	"RunJumpAction.h"

namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class RunJumpState : public State
	{
	private:
		/** �ړ��A�N�V���� */
		RunJumpActionPtr			m_JumpAction;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		RunJumpState()
			: State()
		{
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_JumpAction = Actor()->GetAction<RunJumpAction>(GetKey());
			m_JumpAction->Start();
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_JUMP, 0.3f, 2.0f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);

		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {
			m_JumpAction->Execution();
			// ������Ԃւ̈ڍs
			if (Actor()->GetVelocity()->GetVelocityY() <= 0.0f)
			{
				ChangeState(STATE_KEY_RUNFALL);
			}
		}

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		void InputExecution() override {
			//���E�ňړ�

			if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) ||
				Input()->IsPress(INPUT_KEY_HORIZONTAL) ||
				Input()->IsNegativePress(INPUT_KEY_VERTICAL) ||
				Input()->IsPress(INPUT_KEY_VERTICAL))
			{
				m_JumpAction->Acceleration(Input()->GetAxis(INPUT_KEY_HORIZONTAL), -(Input()->GetAxis(INPUT_KEY_VERTICAL)));
			}


			if (Input()->IsPush(INPUT_KEY_ATTACK))
			{
				ChangeState(STATE_KEY_RUNJUMPATTACK1);
			}

			//�Ή������X�L���̃{�^����������Ă����炻�̃X�L���̃X�e�[�g�Ɉړ�
			for (int i = 0; i < SkillManagerInstance.GetCount(); i++)
			{
				if (!SkillManagerInstance.GetSkill(i)->GetCanUseFlg() || SkillManagerInstance.GetSkill(i)->GetFlyState() == NULL)
				{
					continue;
				}
				if (Input()->IsPush(SkillManagerInstance.GetSkill(i)->GetButton()))
				{

					SkillManagerInstance.GetSkill(i)->Start();
					ChangeState(SkillManagerInstance.GetSkill(i)->GetFlyState());
					break;
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
			return STATE_KEY_RUNJUMP;
		}
	};

}