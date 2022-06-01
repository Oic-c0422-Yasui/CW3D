#pragma once


#include	"State.h"
#include	"Skill2_1Action.h"

namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class Skill2_1State : public State
	{
	private:
		/** �ړ��A�N�V���� */
		Skill2_1ActionPtr			m_SkillAction;
		bool						m_NextInputFlg;
		int							m_FrameTime;
		std::vector<ShotPtr>		m_Shots;
		EffectPtr					m_Effect;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Skill2_1State()
			: State()
			, m_NextInputFlg(false)
			, m_FrameTime(0)
		{
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_SkillAction = Actor()->GetAction<Skill2_1Action>(GetKey());

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
			auto attack = Actor()->GetParameterMap()->Get<int>(PARAMETER_KEY_ATTACK);
			attack *= Actor()->GetSkillController()->GetSkill(SKILL_KEY_2)->GetDamage() * 0.01f;
			m_Effect = EffectControllerInstance.Play("Effect4");
			if (Input()->IsNegativePress(INPUT_KEY_VERTICAL))
			{
				if (Actor()->IsReverse())
				{
					float rad = MOF_ToRadian(-30);
					Vector3 direction(cos(rad), sin(rad), 0);
					m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), Vector3(-(2 * direction.x), 0.7f + -(2 * direction.y), 0), 2.0f, attack,0.1f, 0));
					m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), Vector3(-(6 * direction.x), 0.7f + -(6 * direction.y), 0), 2.0f, attack, 0.1f, 0));
					m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), Vector3(-(10 * direction.x),0.7f + -(10 * direction.y), 0), 2.0f, attack, 0.1f, 0));
					EffectControllerInstance.SetRotate(m_Effect->GetHandle(), Vector3(MOF_ToRadian(-30), MOF_ToRadian(-90), 0));
					EffectControllerInstance.SetPosition(m_Effect->GetHandle(), Actor()->GetPosition() + Vector3(-1.7f, 1.2f, 0));

				}
				else
				{
					float rad = MOF_ToRadian(-30);
					Vector3 direction(cos(rad), sin(rad), 0);
					m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), Vector3((2 * direction.x), 0.7f + -(2 * direction.y), 0), 2.0f, attack, 0.1f, 0));
					m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), Vector3((6 * direction.x), 0.7f + -(6 * direction.y), 0), 2.0f, attack, 0.1f, 0));
					m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), Vector3((10 * direction.x), 0.7f + -(10 * direction.y), 0), 2.0f, attack, 0.1f, 0));
					EffectControllerInstance.SetRotate(m_Effect->GetHandle(), Vector3(MOF_ToRadian(-30), MOF_ToRadian(90), 0));
					EffectControllerInstance.SetPosition(m_Effect->GetHandle(), Actor()->GetPosition() + Vector3(1.7f, 1.2f, 0));
				}
			}
			else
			{
				if (Actor()->IsReverse())
				{
					m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), Vector3(-6.0f, 0.7f, 0), Vector3(5.0f, 2.0f, 2.0f), attack, 0.1f, 0));
					EffectControllerInstance.SetRotate(m_Effect->GetHandle(), Vector3(0.0f, MOF_ToRadian(-90), 0.0f));
					EffectControllerInstance.SetPosition(m_Effect->GetHandle(), Actor()->GetPosition() + Vector3(-1.7f, 1.2f, 0));

				}
				else
				{
					m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), Vector3(6.0f, 0.7f, 0), Vector3(5.0f, 2.0f, 2.0f), attack, 0.1f, 0));
					EffectControllerInstance.SetRotate(m_Effect->GetHandle(), Vector3(0.0f, MOF_ToRadian(90), 0.0f));
					EffectControllerInstance.SetPosition(m_Effect->GetHandle(), Actor()->GetPosition() + Vector3(1.7f, 1.2f, 0));
				}
			}
			
			EffectControllerInstance.SetScale(m_Effect->GetHandle(), Vector3(1.0f, 1.0f, 1.0f));
			EffectControllerInstance.SetSpeed(m_Effect->GetHandle(), 1.2f);


			for (auto& shot : m_Shots)
			{
				shot->SetCollideFlg(false);
				shot->SetKnockBack(Vector3(0.5f, 0.2f, 0));
			}

			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_SKILL2_1, 0.7f, 2.0f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {

			for (auto& shot : m_Shots)
			{
				shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
				if (m_FrameTime < 15)
				{
					shot->SetCollideFlg(false);


				}
				else if (!shot->GetCollideFlg())
				{
					shot->SetCollideFlg(true);
				}
				if (m_FrameTime > 20)
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
				if (m_FrameTime > 30)
				{
					if (Actor()->GetTransform()->GetPositionY() > 0)
					{
						ChangeState(STATE_KEY_FALL);
					}
					else
					{
						ChangeState(STATE_KEY_IDLE);
					}
				}
				

			}


		}

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		void InputExecution() override {


			//�Ή������X�L���̃{�^����������Ă����炻�̃X�L���̃X�e�[�g�Ɉړ�
			for (int i = 0; i < Actor()->GetSkillController()->GetCount(); i++)
			{
				if (!Actor()->GetSkillController()->GetSkill(i)->GetCanUseFlg() || Actor()->GetSkillController()->GetSkill(i)->GetState() == NULL)
				{
					continue;
				}
				if (Input()->IsPush(Actor()->GetSkillController()->GetSkill(i)->GetButton()))
				{

					Actor()->GetSkillController()->GetSkill(i)->Start();
					//���ɕ����Ă���΋󒆔���
					if (Actor()->GetTransform()->GetPositionY() > 0)
					{
						ChangeState(Actor()->GetSkillController()->GetSkill(i)->GetFlyState());
					}
					else
					{
						ChangeState(Actor()->GetSkillController()->GetSkill(i)->GetState());
					}
					break;
				}
			}
		}



		/**
		 * @brief		�X�e�[�g���̏I������
		 */
		void End() override {
			m_SkillAction->End();
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
			return STATE_KEY_SKILL2_1;
		}
	};

}