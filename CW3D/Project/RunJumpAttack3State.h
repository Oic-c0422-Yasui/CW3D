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
		struct Parameter
		{
			float CollideFirstStartFrameTime;
			float CollideSecondStartFrameTime;
			ShotAABB ShotStatus;
			EffectCreateParameter EffectStatus;
		};
	private:
		Parameter m_Parameter;
		/** �ړ��A�N�V���� */
		RunJumpAttack3ActionPtr			m_Attack3Action;

		const float CollideStartFrameTime = GameFrameTime * 12.0f;
		const float CollideEndFrameTime = GameFrameTime * 40.0f;
		bool collideStartFlg;

		//1:offset(Vector3) 2:nextHitTime(float) 3:damage(int) 4:knockBack(Vector3)
		//5:collideFlg(bool) 6:type(int) 7:size(Vector3)
		ShotAABB createShotStatus = { Vector3(0.7f, 1.2f, 0), 0.3f, 0, Vector3(0.3f, 0.15f, 0.0f),true,CHARA_PLAYER, nullptr, Vector3(1.5f, 2.0f, 1.5f) };
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
			
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_ATTACK3, 0.0f, 1.5f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
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