#pragma once


#include	"State.h"
#include	"JumpAttack1Action.h"

namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class JumpAttack1State : public State
	{
	private:
		/** �ړ��A�N�V���� */
		JumpAttack1ActionPtr			m_JumpAttack1Action;
		bool							m_NextInputFlg;
		int								m_FrameTime;
		std::vector<ShotPtr>			m_Shots;
		EffectPtr						m_Effect;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		JumpAttack1State()
			: State()
			, m_NextInputFlg(false)
			, m_FrameTime(0)
		{
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_JumpAttack1Action = Actor()->GetAction<JumpAttack1Action>(GetKey());
			ShotManagerInstance.Delete();
			m_NextInputFlg = false;
			m_FrameTime = 0;
			m_JumpAttack1Action->Start();
			auto& attack = Actor()->GetParameterMap()->Get<int>(PARAMETER_KEY_ATTACK);
			if (Actor()->IsReverse())
			{
				m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), Vector3(-0.7f, 0.8f, 0), 0.45f, attack, 10.0f, 0));

			}
			else
			{
				m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), Vector3(0.7f, 0.8f, 0), 0.45f, attack, 10.0f, 0));
			}
			for (auto& shot : m_Shots)
			{
				shot->SetCollideFlg(false);
				shot->SetKnockBackX(0.1f);
			}



			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_RUNATTACK1, 0.0f, 1.2f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {

			for (auto& shot : m_Shots)
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
				ChangeState(STATE_KEY_FALL);
			}

		}

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		void InputExecution() override {

			//�Ή������X�L���̃{�^����������Ă����炻�̃X�L���̃X�e�[�g�Ɉړ�
			for (int i = 0; i < Actor()->GetSkillController()->GetCount(); i++)
			{
				if (!Actor()->GetSkillController()->GetSkill(i)->GetCanUseFlg() || Actor()->GetSkillController()->GetSkill(i)->GetFlyState() == NULL)
				{
					continue;
				}
				if (Input()->IsPush(Actor()->GetSkillController()->GetSkill(i)->GetButton()))
				{

					Actor()->GetSkillController()->GetSkill(i)->Start();
					ChangeState(Actor()->GetSkillController()->GetSkill(i)->GetFlyState());
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
			return STATE_KEY_JUMPATTACK1;
		}
	};

}