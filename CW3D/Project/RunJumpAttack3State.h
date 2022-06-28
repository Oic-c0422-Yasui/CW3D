#pragma once


#include	"AttackBaseState.h"
#include	"RunJumpAttack3Action.h"

namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class RunJumpAttack3State : public AttackBaseState
	{
	public:
		struct Parameter : public BaseParam
		{
			float CollideFirstStartFrameTime;
			float CollideSecondStartFrameTime;
			ShotAABB ShotStatus;
		};
	private:
		Parameter m_Parameter;
		/** �ړ��A�N�V���� */
		RunJumpAttack3ActionPtr			m_Attack3Action;


		bool collideStartFlg;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		RunJumpAttack3State(Parameter param)
			: AttackBaseState()
			, m_Parameter(param)
			, collideStartFlg(false)
		{
		}

		const ShotAABB& GetCreateShotStatusAABB() override { return m_Parameter.ShotStatus; }

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_Attack3Action = Actor()->GetAction<RunJumpAttack3Action>(GetKey());
			AttackBaseState::Start();
			collideStartFlg = false;
			m_Attack3Action->Start();
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
				if (m_CurrentTime >= m_Parameter.CollideFirstStartFrameTime && !collideStartFlg)
				{
						m_Attack3Action->Execution();
						m_Attack3Action->Jump();

				}
				else if (m_CurrentTime >= m_Parameter.CollideSecondStartFrameTime && shot->GetCollideFlg())
				{
					shot->SetCollideFlg(false);
				}

			}
			if (m_CurrentTime >= m_Parameter.CollideFirstStartFrameTime && !collideStartFlg)
			{
				collideStartFlg = true;
			}

			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				ChangeState(STATE_KEY_FALL);
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
			return STATE_KEY_RUNJUMPATTACK3;
		}
	};

}