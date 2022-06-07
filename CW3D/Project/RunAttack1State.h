#pragma once


#include	"AttackBaseState.h"
#include	"RunAttack1Action.h"

namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class RunAttack1State : public AttackBaseState
	{
	private:
		/** �ړ��A�N�V���� */
		RunAttack1ActionPtr			m_RunAttack1Action;

		//1:offset(Vector3) 2:nextHitTime(float) 3:damage(int) 4:knockBack(Vector3)
		//5:collideFlg(bool) 6:type(int) 7:size(Vector3)
		const ShotAABB createShotStatus = { Vector3(0.7f, 0.8f, 0), 0.5f, 0, Vector3(0.4f, 0.0f, 0.0f),false,0, Vector3(1.2f, 1.5f, 0.8f) };

		//1:name(string) 2:offset(Vector3) 3:scale(Vector3) 4:rotate(Vector3)
		//5:speed(float)
		const EffectCreateParameter createEffectStatus = { "Effect2", Vector3(0.8f, 1.0f, 0), Vector3(0.3f, 0.4f, 0.0f), Vector3(0.0f, MOF_ToRadian(360.0f), 0.0f),2.0f };
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		RunAttack1State()
			: AttackBaseState()
		{
		}

		const ShotAABB& GetCreateShotStatusAABB() override { return createShotStatus; }
		const EffectCreateParameter& GetCreateEffectStatus() override { return createEffectStatus; }

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_RunAttack1Action = Actor()->GetAction<RunAttack1Action>(GetKey());

			AttackBaseState::Start();

			m_RunAttack1Action->Start();
			//�����蔻��p�̒e�쐬
			CreateShotAABB();
			
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_RUNATTACK1, 0.0f, 1.2f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {
			
			for (auto& shot : m_pShots)
			{
				shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
				if (m_FrameTime == 20)
				{
					shot->SetCollideFlg(true);
				}
				else if (shot->GetCollideFlg())
				{
					shot->SetCollideFlg(false);
				}
			}

			if (m_FrameTime == 20)
			{
				CreateEffect();
			}
			m_FrameTime++;
			

			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				ChangeState(STATE_KEY_IDLE);
			}
			/*else if (m_NextInputFlg)
			{
				if (Actor()->GetAnimationState()->GetTime() > 0.7f)
				{
					ChangeState(STATE_KEY_ATTACK2);
				}
			}*/
		}

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		void InputExecution() override {

			if (m_FrameTime > 40)
			{
				if (Input()->IsPush(INPUT_KEY_ATTACK))
				{
					ChangeState(STATE_KEY_ATTACK1);
				}
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
			return STATE_KEY_RUNATTACK1;
		}
	};

}