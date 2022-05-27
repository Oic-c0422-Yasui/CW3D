#pragma once

#include	"State.h"
#include	"RunLandingAction.h"

namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class RunLandingState : public State
	{
	private:
		/** �ړ��A�N�V���� */
		RunLandingActionPtr			m_LandingAction;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		RunLandingState()
			: State()
		{
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_LandingAction = Actor()->GetAction<RunLandingAction>(GetKey());
			m_LandingAction->Start();
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_LANDING, 0.0f, 1.0f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);

		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {
			m_LandingAction->Execution();
			// ������Ԃւ̈ڍs
			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				ChangeState(STATE_KEY_IDLE);
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
				ChangeState(STATE_KEY_RUN);
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
			return STATE_KEY_RUNLANDING;
		}
	};

}