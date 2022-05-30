#pragma once

#include	"State.h"
#include	"FlyDamageAction.h"

namespace Sample {

	/**
	 * @brief		�_���[�W�X�e�[�g
	 */
	class FlyDamageState : public State
	{
	private:
		//�_���[�W�X�e�[�g
		FlyDamageActionPtr			m_DamageAction;
		//�E�F�C�g
		int						wait;
		//���ݎ���
		int						currentTime;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		FlyDamageState()
			: State()
			, wait(0)
			, currentTime(0) {
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_DamageAction = Actor()->GetAction<FlyDamageAction>(GetKey());
			m_DamageAction->Start();
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_FLYDAMAGE, 0.0f, 1.2f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {
			m_DamageAction->Execution();
			currentTime++;
			if (Actor()->GetTransform()->GetPositionY() <= 0)
			{
				auto& hp = Actor()->GetParameterMap()->Get<int>(PARAMETER_KEY_HP);
				if (hp <= 0)
				{
					ChangeState(STATE_KEY_DEAD);
				}
				else
				{
					ChangeState(STATE_KEY_DOWN);
				}
				
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
			return STATE_KEY_FLYDAMAGE;
		}
	};
}
