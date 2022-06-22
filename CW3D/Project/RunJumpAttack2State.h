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
		struct Parameter
		{
			float NextInputFrameTime;
			ShotAABB ShotStatus;
		};
	private:
		Parameter m_Parameter;
		/** �ړ��A�N�V���� */
		RunJumpAttack2ActionPtr			m_Attack2Action;

		const float NextInputFrameTime = GameFrameTime * 20.0f;

		//1:offset(Vector3) 2:nextHitTime(float) 3:damage(int) 4:knockBack(Vector3)
		//5:collideFlg(bool) 6:type(int) 7:size(Vector3)
		ShotAABB createShotStatus = { Vector3(0.7f, 0.7f, 0), 10.0f, 0, Vector3(0.2f, 0.2f, 0.0f),true,CHARA_PLAYER, nullptr, Vector3(1.5f, 1.5f, 1.5f) };
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
			//Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_ATTACK2, 0.0f, 1.5f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
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