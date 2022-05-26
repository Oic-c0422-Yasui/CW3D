#pragma once


#include	"State.h"
#include	"RunAttack1Action.h"

namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class RunAttack1State : public State
	{
	private:
		/** �ړ��A�N�V���� */
		RunAttack1ActionPtr			m_RunAttack1Action;
		bool					m_NextInputFlg;
		int						m_FrameTime;
		std::vector<ShotPtr>	m_Shots;
		EffectPtr				m_Effect;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		RunAttack1State()
			: State()
			, m_NextInputFlg(false)
			, m_FrameTime(0)
		{
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_RunAttack1Action = Actor()->GetAction<RunAttack1Action>(GetKey());
			ShotManagerInstance.Delete();
			m_NextInputFlg = false;
			m_FrameTime = 0;
			m_RunAttack1Action->Start();
			if (Actor()->IsReverse())
			{
				m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition() + Vector3(-0.7f, 0.8f, 0), 0.45f, 0));

			}
			else
			{
				m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition() + Vector3(0.7f, 0.8f, 0), 0.45f, 0));
			}
			for (auto& shot : m_Shots)
			{
				shot->SetCollideFlg(false);
				shot->SetKnockBack(0.4f);
			}
			
			
			
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_RUNATTACK1, 0.0f, 1.2f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {
			
			for (auto& shot : m_Shots)
			{
				shot->AddPosition(Actor()->GetVelocity()->GetVelocity());
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
				m_Effect = EffectControllerInstance.Play("Effect2");
				if (Actor()->IsReverse())
				{
					EffectControllerInstance.SetRotate(m_Effect->GetHandle(), Vector3(0.0f, MOF_ToRadian(180.0f), 0.0f));
					EffectControllerInstance.SetPosition(m_Effect->GetHandle(), Actor()->GetPosition() + Vector3(-0.8f, 1.0f, 0));
				}
				else
				{
					EffectControllerInstance.SetRotate(m_Effect->GetHandle(), Vector3(0.0f, 0, 0.0f));
					EffectControllerInstance.SetPosition(m_Effect->GetHandle(), Actor()->GetPosition() + Vector3(0.8f, 1.0f, 0));
				}
				EffectControllerInstance.SetScale(m_Effect->GetHandle(), Vector3(0.3f, 0.4f, 0.0f));
				EffectControllerInstance.SetSpeed(m_Effect->GetHandle(), 2.0f);
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
			
			//�Ή������X�L���̃{�^����������Ă����炻�̃X�L���̃X�e�[�g�Ɉړ�
			for (int i = 0; i < SkillManagerInstance.GetCount(); i++)
			{
				if (!SkillManagerInstance.GetSkill(i)->GetCanUseFlg())
				{
					continue;
				}
				if (Input()->IsPush(SkillManagerInstance.GetSkill(i)->GetButton()))
				{
					ChangeState(SkillManagerInstance.GetSkill(i)->GetName());
					break;
				}
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
			return STATE_KEY_RUNATTACK1;
		}
	};

}