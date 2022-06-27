#pragma once


#include	"AttackBaseState.h"
#include	"EscapeAction.h"


namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class EscapeState : public AttackBaseState
	{
	public:
		struct Parameter
		{
			//float NextInputFrameTime;
		};
	private:
		Parameter m_Parameter;

		/** �ړ��A�N�V���� */
		EscapeActionPtr			m_EscapeAction;


	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		EscapeState(Parameter param)
			: AttackBaseState()
			, m_Parameter(param)
		{
		}

		//const EffectCreateParameter& GetCreateEffectStatus() override { return m_Parameter.EffectStatus; }

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_EscapeAction = Actor()->GetAction<EscapeAction>(GetKey());
			AttackBaseState::Start();

			m_EscapeAction->Start();

			if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) ||
				Input()->IsPress(INPUT_KEY_HORIZONTAL))
			{
				m_EscapeAction->Move(Input()->GetAxis(INPUT_KEY_HORIZONTAL), -(Input()->GetAxis(INPUT_KEY_VERTICAL)));
			}
			else
			{
				if (Actor()->IsReverse())
				{
					m_EscapeAction->Move(1, -(Input()->GetAxis(INPUT_KEY_VERTICAL)));
				}
				else
				{
					m_EscapeAction->Move(-1, - (Input()->GetAxis(INPUT_KEY_VERTICAL)));
				}
			}
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {


			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				if (Actor()->GetTransform()->GetPositionY() > 0)
				{
					ChangeState(STATE_KEY_FALL);
				}
				else
				{
					ChangeState(STATE_KEY_IDLE);
				}
			}
			AttackBaseState::Execution();
		}

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		void InputExecution() override {

			AttackBaseState::InputExecution();
		}



		/**
		 * @brief		�X�e�[�g���̏I������
		 */
		void End() override {
			AttackBaseState::End();
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
			return STATE_KEY_ESCAPE;
		}
	};

}