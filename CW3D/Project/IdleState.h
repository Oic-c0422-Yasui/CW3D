#pragma once

#include	"State.h"
#include	"IdleAction.h"

namespace Sample {

	/**
	 * @brief		�ҋ@�X�e�[�g
	 */
	class IdleState : public State
	{
	private:
		/** �ړ��A�N�V���� */
		IdleActionPtr			m_IdleAction;
		float					m_Time;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		IdleState()
			: State()
			, m_Time(0.0f)
		{
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_IdleAction = Actor()->GetAction<IdleAction>(GetKey());
			m_Time = 0.0f;
			m_IdleAction->Start();
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_IDLE, 0.0f, 1.0f, 0.25f, TRUE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {
			if (m_Time < 5.0f)
			{
				m_Time += CUtilities::GetFrameSecond();
			}
			else
			{
				ChangeState(STATE_KEY_IDLEMOTION);
				
			}
		}

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		void InputExecution() override {
			if (Input()->IsNegativeDoublePush(INPUT_KEY_HORIZONTAL) || Input()->IsDoublePush(INPUT_KEY_HORIZONTAL) ||
				Input()->IsNegativeDoublePush(INPUT_KEY_VERTICAL) || Input()->IsDoublePush(INPUT_KEY_VERTICAL))
			{
				ChangeState(STATE_KEY_RUN);
				//return;
			}
			//�L�[�{�[�h�ł̈ړ�
			else if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) || Input()->IsPress(INPUT_KEY_HORIZONTAL) ||
				Input()->IsNegativePress(INPUT_KEY_VERTICAL) || Input()->IsPress(INPUT_KEY_VERTICAL))
			{
				ChangeState(STATE_KEY_MOVE);
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
			return STATE_KEY_IDLE;
		}
	};

}