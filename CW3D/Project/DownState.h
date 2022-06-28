#pragma once

#include	"State.h"
#include	"DownAction.h"

namespace Sample {

	/**
	 * @brief		�_���[�W�X�e�[�g
	 */
	class DownState : public State
	{
	public:
		struct Parameter
		{
			float endTime;
		};
	private:
		Parameter m_Parameter;

		//�_�E���X�e�[�g
		DownActionPtr				m_DownAction;
		//���ݎ���
		float						m_CurrentTime;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		DownState(Parameter param)
			: State()
			, m_Parameter(param)
			, m_CurrentTime(0) {
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_CurrentTime = 0;
			auto& invincible = Actor()->GetParameterMap()->Get<float>(PARAMETER_KEY_INVINCIBLE);
			invincible = m_Parameter.endTime;
			m_DownAction = Actor()->GetAction<DownAction>(GetKey());
			m_DownAction->Start();
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {
			m_DownAction->Execution();
			//3
			if (m_CurrentTime < m_Parameter.endTime)
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
