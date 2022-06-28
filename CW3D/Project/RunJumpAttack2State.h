#pragma once


#include	"AttackBaseState.h"
#include	"RunJumpAttack2Action.h"

namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class RunJumpAttack2State : public AttackBaseState
	{
	public:
		struct Parameter : public BaseParam
		{
			float NextInputFrameTime;
			ShotAABB ShotStatus;
		};
	private:
		Parameter m_Parameter;
		/** �ړ��A�N�V���� */
		RunJumpAttack2ActionPtr			m_Attack2Action;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		RunJumpAttack2State(Parameter param)
			: AttackBaseState()
			, m_Parameter(param)
		{
		}

		const ShotAABB& GetCreateShotStatusAABB() override { return m_Parameter.ShotStatus; }

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_Attack2Action = Actor()->GetAction<RunJumpAttack2Action>(GetKey());
			AttackBaseState::Start();
			m_Attack2Action->Start();
			//�����蔻��p�̒e�쐬
			CreateShotAABB();
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {


			for (auto& shot : m_pShots)
			{
				shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
			}

			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				ChangeState(STATE_KEY_FALL);
			}
			if (m_NextInputFlg)
			{
				if (m_CurrentTime > m_Parameter.NextInputFrameTime)
				{
					ChangeState(STATE_KEY_RUNJUMPATTACK3);
				}
			}
			AttackBaseState::Execution();
		}

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		void InputExecution() override {

			if (Input()->IsPush(INPUT_KEY_ATTACK))
			{
				m_NextInputFlg = true;
			}

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
			return STATE_KEY_RUNJUMPATTACK2;
		}
	};

}