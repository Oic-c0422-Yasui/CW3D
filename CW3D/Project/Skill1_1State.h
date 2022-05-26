#pragma once


#include	"State.h"
#include	"Skill1_1Action.h"

namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class Skill1_1State : public State
	{
	private:
		/** �ړ��A�N�V���� */
		Skill1_1ActionPtr			m_SkillAction;
		bool						m_NextInputFlg;
		int							m_FrameTime;
		std::vector<ShotPtr>		m_Shots;
		EffectPtr					m_Effect;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Skill1_1State()
			: State()
			, m_NextInputFlg(false)
			, m_FrameTime(0)
		{
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_SkillAction = Actor()->GetAction<Skill1_1Action>(GetKey());

			m_NextInputFlg = false;
			m_FrameTime = 0;
			if (Input()->IsPress(INPUT_KEY_HORIZONTAL))
			{
				Actor()->SetReverse(false);

			}
			else if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL))
			{
				Actor()->SetReverse(true);

			}
			m_SkillAction->Start();
			m_Effect = EffectControllerInstance.Play("Effect3");
			if (Actor()->IsReverse())
			{
				m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition() + Vector3(-6.0f, 0.7f, 0), Vector3(5.0f, 10.0f, 7.0f), 0));
				EffectControllerInstance.SetRotate(m_Effect->GetHandle(), Vector3(0.0f, MOF_ToRadian(-90), 0.0f));
				EffectControllerInstance.SetPosition(m_Effect->GetHandle(), Actor()->GetPosition() + Vector3(-0.8f, -1.5f, 0));

			}
			else
			{
				m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition() + Vector3(6.0f, 0.7f, 0), Vector3(5.0f, 10.0f, 7.0f), 0));
				EffectControllerInstance.SetRotate(m_Effect->GetHandle(), Vector3(0.0f, MOF_ToRadian(90), 0.0f));
				EffectControllerInstance.SetPosition(m_Effect->GetHandle(), Actor()->GetPosition() + Vector3(0.8f, -1.5f, 0));
			}
			EffectControllerInstance.SetScale(m_Effect->GetHandle(), Vector3(1.0f, 1.0f, 1.0f));
			EffectControllerInstance.SetSpeed(m_Effect->GetHandle(), 1.8f);

			
			for (auto& shot : m_Shots)
			{
				shot->SetCollideFlg(false);
				shot->SetKnockBack(0.8f);
			}
			
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_ATTACK1, 0.0f, 0.6f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {

			for (auto& shot : m_Shots)
			{
				shot->AddPosition(Actor()->GetVelocity()->GetVelocity());
				if (m_FrameTime < 55)
				{
					shot->SetCollideFlg(false);


				}
				else if (!shot->GetCollideFlg())
				{
					shot->SetCollideFlg(true);
				}
				if (m_FrameTime > 80)
				{
					if (shot->GetCollideFlg())
					{
						shot->SetCollideFlg(false);
					}
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

			if (Input()->IsPush(INPUT_KEY_ATTACK))
			{
				m_NextInputFlg = true;
			}


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
			if (m_Effect != nullptr)
			{
				m_Effect->SetStop(true);
				m_Effect.reset();
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
			return STATE_KEY_SKILL1_1;
		}
	};

}