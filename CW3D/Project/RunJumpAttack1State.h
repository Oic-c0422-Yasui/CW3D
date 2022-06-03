#pragma once


#include	"AttackBaseState.h"
#include	"RunJumpAttack1Action.h"

namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class RunJumpAttack1State : public AttackBaseState
	{
	private:
		/** �ړ��A�N�V���� */
		RunJumpAttack1ActionPtr			m_Attack1Action;

		//1:offset(Vector3) 2:nextHitTime(float) 3:damage(int) 4:knockBack(Vector3)
		//5:collideFlg(bool) 6:type(int) 7:size(Vector3)
		ShotAABB createShotStatus = { Vector3(0.8f, 0.7f, 0), 10.0f, 0, Vector3(0.3f, 0.2f, 0.0f),true,0, Vector3(1.5f, 1.5f, 1.5f) };

		//1:name(string) 2:offset(Vector3) 3:scale(Vector3) 4:rotate(Vector3)
		//5:speed(float)
		EffectCreateParameter createEffectStatus = { "Effect2", Vector3(0.8f,0.8f,0), Vector3(0.5f, 0.8f, 0.0f), Vector3(0.0f, MOF_ToRadian(360), 0.0f),1.5f };
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		RunJumpAttack1State()
			: AttackBaseState()
		{
		}

		const ShotAABB& GetCreateShotStatusAABB() override { return createShotStatus; }
		const EffectCreateParameter& GetCreateEffectStatus() override { return createEffectStatus; }
		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_Attack1Action = Actor()->GetAction<RunJumpAttack1Action>(GetKey());
			AttackBaseState::Start();
			m_Attack1Action->Start();
			//�����蔻��p�̒e�쐬
			CreateShotAABB();

			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_ATTACK1, 0.0f, 1.7f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {

			for (auto& shot : m_pShots)
			{
				shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
				
			}
			if (m_FrameTime == 12)
			{
				CreateEffect();
			}

			m_FrameTime++;

			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				ChangeState(STATE_KEY_FALL);
			}
			else if (m_NextInputFlg)
			{
				if (Actor()->GetAnimationState()->GetTime() > 0.35f)
				{
					ChangeState(STATE_KEY_RUNJUMPATTACK2);
				}
			}

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
			return STATE_KEY_RUNJUMPATTACK1;
		}
	};

}