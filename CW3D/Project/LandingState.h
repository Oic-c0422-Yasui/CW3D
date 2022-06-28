#pragma once

#include	"State.h"
#include	"LandingAction.h"

namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class LandingState : public State
	{
	private:
		/** �ړ��A�N�V���� */
		LandingActionPtr			m_LandingAction;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		LandingState()
			: State()
		{
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_LandingAction = Actor()->GetAction<LandingAction>(GetKey());
			m_LandingAction->Start();

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
				ChangeState(STATE_KEY_MOVE);
			}


			if (Input()->IsPush(INPUT_KEY_ATTACK))
			{
				ChangeState(STATE_KEY_ATTACK1);
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
			return STATE_KEY_LANDING;
		}
	};

}