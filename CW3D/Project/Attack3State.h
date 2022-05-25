#pragma once


#include	"State.h"
#include	"Attack3Action.h"

namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class Attack3State : public State
	{
	private:
		/** �ړ��A�N�V���� */
		Attack3ActionPtr			m_Attack3Action;
		bool						m_NextInputFlg;
		int							m_FrameTime;
		std::vector<ShotPtr>		m_Shots;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Attack3State()
			: State()
			, m_NextInputFlg(false)
			, m_FrameTime(0)
		{
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_Attack3Action = Actor()->GetAction<Attack3Action>(GetKey());
			m_FrameTime = 0;
			m_Attack3Action->Start();
			if (Actor()->IsReverse())
			{
				m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition() + Vector3(-0.7f, 0.7f, 0), 0.8f, 0));

			}
			else
			{
				m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition() + Vector3(0.7f, 0.7f, 0), 0.8f, 0));
			}

			for (auto& shot : m_Shots)
			{
				shot->SetCollideFlg(false);
				shot->SetKnockBack(0.3f);
			}
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_ATTACK3, 0.0f, 1.0f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {
			for (auto& shot : m_Shots)
			{
				shot->AddPosition(Actor()->GetVelocity()->GetVelocity());
				if (m_FrameTime == 25 || m_FrameTime == 55)
				{
					shot->SetCollideFlg(true);
					if (m_FrameTime == 25)
					{
						m_Attack3Action->Execution();
					}

				}
				else if (shot->GetCollideFlg())
				{
					shot->SetCollideFlg(false);
				}

			}

			m_FrameTime++;

			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				ChangeState(STATE_KEY_IDLE);
			}
		}

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		void InputExecution() override {

		}



		/**
		 * @brief		�X�e�[�g���̏I������
		 */
		void End() override {
			for (auto& shot : m_Shots)
			{
				shot->SetShow(false);
				shot.reset();
			}
			m_Shots.clear();
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