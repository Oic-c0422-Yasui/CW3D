#pragma once


#include	"State.h"
#include	"Skill3_1Action.h"

namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class Skill3_1State : public State
	{
	private:
		/** �ړ��A�N�V���� */
		Skill3_1ActionPtr			m_SkillAction;
		bool						m_NextInputFlg;
		int							m_FrameTime;
		float						m_CurrentTime;
		float						m_FinishTime;
		std::vector<ShotPtr>		m_Shots;
		EffectPtr					m_Effect;
		bool						m_ContinueFlg;
		std::string					m_Key;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Skill3_1State()
			: State()
			, m_NextInputFlg(false)
			, m_FrameTime(0)
		{
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_SkillAction = Actor()->GetAction<Skill3_1Action>(GetKey());

			m_NextInputFlg = false;
			m_FrameTime = 0;
			m_CurrentTime = 0.0f;
			m_FinishTime = 3.5f;
			m_ContinueFlg = true;
			if (Input()->IsPress(INPUT_KEY_HORIZONTAL))
			{
				Actor()->SetReverse(false);

			}
			else if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL))
			{
				Actor()->SetReverse(true);

			}
			m_SkillAction->Start();
			auto& attack = Actor()->GetParameterMap()->Get<int>(PARAMETER_KEY_ATTACK);
			m_Effect = EffectControllerInstance.Play("Effect5");
			m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), Vector3(0, 0, 0), Vector3(4.0f, 10.0f, 4.0f), attack, 0));
			EffectControllerInstance.SetPosition(m_Effect->GetHandle(), Actor()->GetPosition() + Vector3(0, -1.5f, 0));
			EffectControllerInstance.SetScale(m_Effect->GetHandle(), Vector3(1.0f, 1.0f, 1.0f));
			EffectControllerInstance.SetSpeed(m_Effect->GetHandle(), 1.8f);

			for (int i = 0; i < SkillManagerInstance.GetCount(); i++)
			{
				if (SkillManagerInstance.GetSkill(i)->GetState() != STATE_KEY_SKILL3_1)
				{
					continue;
				}

				m_Key = SkillManagerInstance.GetSkill(i)->GetButton();
				break;
			}

			for (auto& shot : m_Shots)
			{
				shot->SetCollideFlg(false);
				shot->SetKnockBack(Vector3(-0.1f, 0.1f, 0));
			}

			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_SKILL3_1, 0.0f, 0.6f, 0.1f, TRUE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {

			for (auto& shot : m_Shots)
			{
				shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
				if (m_FrameTime % 7  == 0)
				{
					shot->SetCollideFlg(true);
				}
				else if (shot->GetCollideFlg())
				{
					shot->SetCollideFlg(false);
				}

			}
			m_FrameTime++;

			EffectControllerInstance.SetPosition(m_Effect->GetHandle(), Actor()->GetPosition() + Vector3(0, -1.5f, 0));

			m_CurrentTime += CUtilities::GetFrameSecond();

			if (m_CurrentTime > m_FinishTime || !m_ContinueFlg)
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

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		void InputExecution() override {

			if (Input()->IsPress(m_Key))
			{
				m_ContinueFlg = true;
			}
			else
			{
				m_ContinueFlg = false;
			}

			if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) ||
				Input()->IsPress(INPUT_KEY_HORIZONTAL) ||
				Input()->IsNegativePress(INPUT_KEY_VERTICAL) ||
				Input()->IsPress(INPUT_KEY_VERTICAL))
			{
				m_SkillAction->Acceleration(Input()->GetAxis(INPUT_KEY_HORIZONTAL), -(Input()->GetAxis(INPUT_KEY_VERTICAL)));
			}

			//�Ή������X�L���̃{�^����������Ă����炻�̃X�L���̃X�e�[�g�Ɉړ�
			for (int i = 0; i < SkillManagerInstance.GetCount(); i++)
			{
				if (!SkillManagerInstance.GetSkill(i)->GetCanUseFlg() || SkillManagerInstance.GetSkill(i)->GetState() == NULL)
				{
					continue;
				}
				if (Input()->IsPush(SkillManagerInstance.GetSkill(i)->GetButton()))
				{

					SkillManagerInstance.GetSkill(i)->Start();
					//���ɕ����Ă���΋󒆔���
					if (Actor()->GetTransform()->GetPositionY() > 0)
					{
						ChangeState(SkillManagerInstance.GetSkill(i)->GetFlyState());
					}
					else
					{
						ChangeState(SkillManagerInstance.GetSkill(i)->GetState());
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
			return STATE_KEY_SKILL3_1;
		}
	};

}