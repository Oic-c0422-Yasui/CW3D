#pragma once


#include	"State.h"
#include	"RunJumpAttack1Action.h"

namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class RunJumpAttack1State : public State
	{
	private:
		/** �ړ��A�N�V���� */
		RunJumpAttack1ActionPtr			m_Attack1Action;
		bool					m_NextInputFlg;
		int						m_FrameTime;
		std::vector<ShotPtr>	m_Shots;
		EffectPtr				m_Effect;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		RunJumpAttack1State()
			: State()
			, m_NextInputFlg(false)
			, m_FrameTime(0)
		{
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_Attack1Action = Actor()->GetAction<RunJumpAttack1Action>(GetKey());

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
			auto& attack = Actor()->GetParameterMap()->Get<int>(PARAMETER_KEY_ATTACK);
			if (Actor()->IsReverse())
			{
				m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), Vector3(-0.8f, 0.7f, 0), 1.5f, attack, 0));

			}
			else
			{
				m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), Vector3(0.8f, 0.7f, 0), 1.5f, attack, 0));
			}

			m_FrameTime = 0;

			for (auto& shot : m_Shots)
			{
				shot->SetCollideFlg(false);
				shot->SetKnockBack(Vector3(0.3f, 0.2f, 0));
			}
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_ATTACK1, 0.0f, 1.7f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {

			for (auto& shot : m_Shots)
			{
				shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
				if (m_FrameTime == 12)
				{
					shot->SetCollideFlg(true);


				}
				else if (shot->GetCollideFlg())
				{
					shot->SetCollideFlg(false);
				}

			}
			if (m_FrameTime == 12)
			{
				m_Effect = EffectControllerInstance.Play("Effect2");
				if (Actor()->IsReverse())
				{
					EffectControllerInstance.SetRotate(m_Effect->GetHandle(), Vector3(0.0f, MOF_ToRadian(180.0f), 0.0f));
					EffectControllerInstance.SetPosition(m_Effect->GetHandle(), Actor()->GetPosition() + Vector3(-0.8f, 0.8f, 0));


				}
				else
				{
					EffectControllerInstance.SetRotate(m_Effect->GetHandle(), Vector3(0.0f, 0, 0.0f));
					EffectControllerInstance.SetPosition(m_Effect->GetHandle(), Actor()->GetPosition() + Vector3(0.8f, 0.8f, 0));
				}
				EffectControllerInstance.SetScale(m_Effect->GetHandle(), Vector3(0.5f, 0.8f, 0.0f));
				EffectControllerInstance.SetSpeed(m_Effect->GetHandle(), 1.5f);
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
			return STATE_KEY_RUNJUMPATTACK1;
		}
	};

}