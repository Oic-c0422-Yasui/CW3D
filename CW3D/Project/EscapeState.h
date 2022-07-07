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
		struct Parameter : public BaseParam
		{
			float ThroughStartTime;
			float ThroughEndTime;
			float EscapeStartTime;
			float EscapeTime;
		};
	private:
		Parameter m_Parameter;

		/** �ړ��A�N�V���� */
		EscapeActionPtr			m_EscapeAction;

		bool m_ThroughFlg;
		bool m_EscapeFlg;
		float m_EscapeCurrentTime;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		EscapeState(Parameter param)
			: AttackBaseState()
			, m_Parameter(param)
			, m_ThroughFlg(false)
			, m_EscapeCurrentTime(0.0f)
			, m_EscapeFlg(false)
		{
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_EscapeAction = Actor()->GetAction<EscapeAction>(GetKey());
			AttackBaseState::Start();
			m_ThroughFlg = false;
			m_EscapeFlg = false;
			m_EscapeCurrentTime = 0.0f;
			m_EscapeAction->Start();
			Actor()->SetArmorLevel(m_Parameter.armorLevel);

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

			if (m_CurrentTime > m_Parameter.ThroughStartTime && !m_ThroughFlg)
			{
				m_EscapeAction->StartThrough();
				m_ThroughFlg = true;
			}

			//�W���X�g�������
			if (m_CurrentTime >= m_Parameter.EscapeStartTime)
			{
				
				if (m_EscapeCurrentTime < m_Parameter.EscapeTime)
				{
					auto& isEscape = Actor()->GetParameterMap()->Get<bool>(PARAMETER_KEY_ESCAPE);
					if (!isEscape)
					{
						isEscape = true;
					}
					m_EscapeCurrentTime += CUtilities::GetFrameSecond() * TimeControllerInstance.GetTimeScale(Actor()->GetType());
					if (m_EscapeCurrentTime >= m_Parameter.EscapeTime)
					{
						isEscape = false;
					}

				}
			}

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
			if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) ||
				Input()->IsPress(INPUT_KEY_HORIZONTAL) ||
				Input()->IsNegativePress(INPUT_KEY_VERTICAL) ||
				Input()->IsPress(INPUT_KEY_VERTICAL))
			{
				if (m_CurrentTime > m_Parameter.ThroughEndTime)
				{
					if (Actor()->GetTransform()->GetPositionY() > 0)
					{
						if (GetKeepKey() == STATE_KEY_RUN)
						{
							ChangeState(STATE_KEY_RUNFALL);
						}
						else
						{
							ChangeState(STATE_KEY_FALL);
						}
					}
					else
					{
						if (GetKeepKey() == STATE_KEY_RUN)
						{
							ChangeState(STATE_KEY_RUN);
						}
						else
						{
							ChangeState(STATE_KEY_MOVE);
						}
					}
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
			m_EscapeAction->End();
			auto& isEscape = Actor()->GetParameterMap()->Get<bool>(PARAMETER_KEY_ESCAPE);
			isEscape = false;
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