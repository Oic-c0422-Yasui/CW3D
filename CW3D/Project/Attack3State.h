#pragma once


#include	"AttackBaseState.h"
#include	"Attack3Action.h"

namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class Attack3State : public AttackBaseState
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
		Attack3ActionPtr			m_Attack3Action;


		bool collideFirstStartFlg;
		bool collideSecondStartFlg;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Attack3State(Parameter param)
			: AttackBaseState()
			, m_Parameter(param)
			, collideFirstStartFlg(false)
			, collideSecondStartFlg(false)
		{
		}

		const ShotAABB& GetCreateShotStatusAABB() override { return m_Parameter.ShotStatus; }

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_Attack3Action = Actor()->GetAction<Attack3Action>(GetKey());

			AttackBaseState::Start();

			m_Attack3Action->Start();
			collideFirstStartFlg = false;
			collideSecondStartFlg = false;
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
				if ((m_CurrentTime >= m_Parameter.CollideFirstStartFrameTime && !collideFirstStartFlg) 
					|| (m_CurrentTime >= m_Parameter.CollideSecondStartFrameTime && !collideSecondStartFlg))
				{
					shot->SetCollideFlg(true);
					if (m_CurrentTime >= m_Parameter.CollideFirstStartFrameTime && !collideFirstStartFlg)
					{
						m_Attack3Action->Execution();
						
					}

				}
				else if (shot->GetCollideFlg())
				{
					shot->SetCollideFlg(false);
				}

			}
			if (m_CurrentTime >= m_Parameter.CollideFirstStartFrameTime && !collideFirstStartFlg)
			{
				collideFirstStartFlg = true;
			}
			if (m_CurrentTime >= m_Parameter.CollideSecondStartFrameTime && !collideSecondStartFlg)
			{
				collideSecondStartFlg = true;
			}
;

			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				ChangeState(STATE_KEY_IDLE);
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
			return STATE_KEY_ATTACK3;
		}
	};

}