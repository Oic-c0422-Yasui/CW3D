#pragma once

#include	"State.h"
#include	"DeadAction.h"

namespace Sample {

	/**
	 * @brief		�_���[�W�X�e�[�g
	 */
	class DeadState : public State
	{
	private:
		//�_���[�W�X�e�[�g
		DeadActionPtr			m_DeadAction;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		DeadState()
			: State()
		{
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_DeadAction = Actor()->GetAction<DeadAction>(GetKey());
			m_DeadAction->Start();
			//Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_DOWN, 0.0f, 1.2f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {
			m_DeadAction->Execution();
		}

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		void InputExecution() override {
		}

		/**
		 * @brief		�X�e�[�g���̏I������
		 */
		void End() override {
			m_DeadAction->End();
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
			return STATE_KEY_DEAD;
		}
	};
}
