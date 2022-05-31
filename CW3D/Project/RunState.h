#pragma once

#include	"State.h"
#include	"RunAction.h"

namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class RunState : public State
	{
	private:
		/** �ړ��A�N�V���� */
		RunActionPtr			runAction_;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		RunState()
			: State() {
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			runAction_ = Actor()->GetAction<RunAction>(STATE_KEY_RUN);
			if (Input()->IsPress(INPUT_KEY_HORIZONTAL))
			{
				Actor()->SetReverse(false);
			}
			else if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL))
			{
				Actor()->SetReverse(true);
			}
			runAction_->Start();
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_RUN, 0.0f, 1.0f, 0.12f, TRUE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {
			runAction_->Execution();
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
				runAction_->Acceleration(Input()->GetAxis(INPUT_KEY_HORIZONTAL), -(Input()->GetAxis(INPUT_KEY_VERTICAL)));
			}
			else
			{
				ChangeState(STATE_KEY_IDLE);
			}

			if (Input()->IsPush(INPUT_KEY_ATTACK))
			{
				ChangeState(STATE_KEY_RUNATTACK1);
			}

			if (Input()->IsPush(INPUT_KEY_JUMP))
			{
				ChangeState(STATE_KEY_RUNJUMP);
			}

			//�Ή������X�L���̃{�^����������Ă����炻�̃X�L���̃X�e�[�g�Ɉړ�
			for (int i = 0; i < Actor()->GetSkillController()->GetCount(); i++)
			{
				if (!Actor()->GetSkillController()->GetSkill(i)->GetCanUseFlg() || Actor()->GetSkillController()->GetSkill(i)->GetState() == NULL)
				{
					continue;
				}
				if (Input()->IsPush(Actor()->GetSkillController()->GetSkill(i)->GetButton()))
				{

					Actor()->GetSkillController()->GetSkill(i)->Start();
					ChangeState(Actor()->GetSkillController()->GetSkill(i)->GetState());
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
			return STATE_KEY_RUN;
		}
	};

}