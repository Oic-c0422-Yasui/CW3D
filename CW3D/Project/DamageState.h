#pragma once

#include	"State.h"
#include	"DamageAction.h"

namespace Sample {

	/**
	 * @brief		�_���[�W�X�e�[�g
	 */
	class DamageState : public State
	{
	public:
		struct Parameter
		{
			float time;
		};
	private:
		Parameter m_Parameter;
		//�_���[�W�X�e�[�g
		DamageActionPtr			m_DamageAction;
		//���ݎ���
		float						m_CurrentTime;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		DamageState(Parameter param)
			: State()
			, m_Parameter(param)
			, m_CurrentTime(0.0f) {
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_CurrentTime = 0.0f;
			m_DamageAction = Actor()->GetAction<DamageAction>(GetKey());
			m_DamageAction->Start();
			
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {
			m_DamageAction->Execution();

			if (Actor()->GetTransform()->GetPositionY() > 0)
			{
				ChangeState(STATE_KEY_FLYDAMAGE);
			}
			
			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				ChangeState(STATE_KEY_IDLE);
			}
			auto& hp = Actor()->GetParameterMap()->Get<Sample::ReactiveParameter<int>>(PARAMETER_KEY_HP);
			if (hp <= 0)
			{
				ChangeState(STATE_KEY_DEAD);
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
			m_DamageAction->End();
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
			return STATE_KEY_DAMAGE;
		}
	};
}
