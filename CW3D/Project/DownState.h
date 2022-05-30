#pragma once

#include	"State.h"
#include	"DownAction.h"

namespace Sample {

	/**
	 * @brief		�_���[�W�X�e�[�g
	 */
	class DownState : public State
	{
	private:
		//�_���[�W�X�e�[�g
		DownActionPtr			m_DownAction;
		//�I������
		float						m_FinishTime;
		//���ݎ���
		float						m_CurrentTime;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		DownState()
			: State()
			, m_FinishTime(0)
			, m_CurrentTime(0) {
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_CurrentTime = 0;
			m_FinishTime = 3;
			auto& invincible = Actor()->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
			invincible = m_FinishTime;
			m_DownAction = Actor()->GetAction<DownAction>(GetKey());
			m_DownAction->Start();
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_DOWN, 0.0f, 1.2f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {
			m_DownAction->Execution();
			if (m_CurrentTime < m_FinishTime)
			{
				m_CurrentTime += CUtilities::GetFrameSecond();
			}
			else
			{
				ChangeState(STATE_KEY_IDLE);
			}
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
			m_DownAction->End();
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
			return STATE_KEY_DOWN;
		}
	};
}
