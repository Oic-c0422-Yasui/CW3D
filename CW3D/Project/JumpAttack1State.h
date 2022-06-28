#pragma once


#include	"AttackBaseState.h"
#include	"JumpAttack1Action.h"


namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class JumpAttack1State : public AttackBaseState
	{
	public:
		struct Parameter : public BaseParam
		{
			float CollideStartFrameTime;
			ShotAABB ShotStatus;
			EffectCreateParameter EffectStatus;
		};
	private:
		Parameter m_Parameter;
		/** �ړ��A�N�V���� */
		JumpAttack1ActionPtr			m_JumpAttack1Action;

		const float EffectStartFrameTime = GameFrameTime * 20.0f;

		bool collideStartFlg;


	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		JumpAttack1State(Parameter param)
			: AttackBaseState()
			, m_Parameter(param)
			, collideStartFlg(false)
		{
		}
		const ShotAABB& GetCreateShotStatusAABB() override { return m_Parameter.ShotStatus; }
		const EffectCreateParameter& GetCreateEffectStatus() override { return m_Parameter.EffectStatus; }

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_JumpAttack1Action = Actor()->GetAction<JumpAttack1Action>(GetKey());
			AttackBaseState::Start();
			m_JumpAttack1Action->Start();
			collideStartFlg = false;

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
				if (m_CurrentTime >= m_Parameter.CollideStartFrameTime && !collideStartFlg)
				{
					shot->SetCollideFlg(true);

				}
			}

			if (m_CurrentTime >= m_Parameter.CollideStartFrameTime && !collideStartFlg)
			{
				CreateEffect();
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
			return STATE_KEY_JUMPATTACK1;
		}
	};

}