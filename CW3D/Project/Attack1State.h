#pragma once


#include	"State.h"
#include	"Attack1Action.h"

namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class Attack1State : public State
	{
	private:
		/** �ړ��A�N�V���� */
		Attack1ActionPtr			m_Attack1Action;
		bool					m_NextInputFlg;
		int						m_ShotId;
		int						m_FrameTime;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Attack1State()
			: State()
			, m_NextInputFlg(false)
			, m_ShotId(-1)
			, m_FrameTime(0)
		{
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_Attack1Action = Actor()->GetAction<Attack1Action>(GetKey());

			m_NextInputFlg = false;
			if (Input()->IsPress(INPUT_KEY_HORIZONTAL))
			{
				Actor()->SetReverse(false);
				
			}
			else if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL))
			{
				Actor()->SetReverse(true);
				
			}
			m_Attack1Action->Start();
			if (Actor()->IsReverse())
			{
				ShotManagerInstance.Create(Actor()->GetPosition() + Vector3(-0.8f, 0.7f, 0), 1.2f, 0, 0);
				
			}
			else
			{
				ShotManagerInstance.Create(Actor()->GetPosition() + Vector3(0.8f, 0.7f, 0), 1.2f, 0, 0);
			}
			m_FrameTime = 0;
			m_ShotId = ShotManagerInstance.GetShotBackId();
			ShotManagerInstance.GetShot(m_ShotId)->SetHide(true);
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_ATTACK1, 0.0f,1.2f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {

			if (ShotManagerInstance.GetShot(m_ShotId) != nullptr)
			{
				ShotManagerInstance.GetShot(m_ShotId)->AddPosition(Actor()->GetVelocity()->GetVelocity());
				if (m_FrameTime == 25)
				{
					ShotManagerInstance.GetShot(m_ShotId)->SetHide(false);
				}
				else if (!ShotManagerInstance.GetShot(m_ShotId)->IsHide())
				{
					ShotManagerInstance.GetShot(m_ShotId)->SetHide(true);
				}
			}
			
			m_FrameTime++;

			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				ChangeState(STATE_KEY_IDLE);
			}
			else if (m_NextInputFlg)
			{
				if (Actor()->GetAnimationState()->GetTime() > 0.7f)
				{
					ChangeState(STATE_KEY_ATTACK2);
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

			
		}



		/**
		 * @brief		�X�e�[�g���̏I������
		 */
		void End() override {
			if (m_ShotId > -1)
			{
				ShotManagerInstance.GetShot(m_ShotId)->SetShow(false);
				ShotManagerInstance.Delete();
			}
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
			return STATE_KEY_ATTACK1;
		}
	};

}