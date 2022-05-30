#pragma once


#include	"State.h"
#include	"RunJumpAttack2Action.h"

namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class RunJumpAttack2State : public State
	{
	private:
		/** �ړ��A�N�V���� */
		RunJumpAttack2ActionPtr			m_Attack2Action;
		bool						m_NextInputFlg;
		int							m_FrameTime;
		std::vector<ShotPtr>		m_Shots;
		EffectPtr					m_Effect;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		RunJumpAttack2State()
			: State()
			, m_NextInputFlg(false)
			, m_FrameTime(0)
		{
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_Attack2Action = Actor()->GetAction<RunJumpAttack2Action>(GetKey());
			m_FrameTime = 0;
			m_NextInputFlg = false;
			m_Attack2Action->Start();
			auto& attack = Actor()->GetParameterMap()->Get<int>(PARAMETER_KEY_ATTACK);
			if (Actor()->IsReverse())
			{
				m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), Vector3(-0.7f, 0.7f, 0), 1.5f, attack, 0));

			}
			else
			{
				m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), Vector3(0.7f, 0.7f, 0), 1.5f, attack, 0));
			}
			for (auto& shot : m_Shots)
			{
				shot->SetCollideFlg(false);
				shot->SetKnockBack(Vector3(0.2f, 0.2f, 0));
			}
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_ATTACK2, 0.0f, 1.5f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
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

			m_FrameTime++;
			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				ChangeState(STATE_KEY_FALL);
			}
			if (m_NextInputFlg)
			{
				if (m_FrameTime > 20)
				{
					ChangeState(STATE_KEY_RUNJUMPATTACK3);
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
			for (int i = 0; i < SkillManagerInstance.GetCount(); i++)
			{
				if (!SkillManagerInstance.GetSkill(i)->GetCanUseFlg() || SkillManagerInstance.GetSkill(i)->GetFlyState() == NULL)
				{
					continue;
				}
				if (Input()->IsPush(SkillManagerInstance.GetSkill(i)->GetButton()))
				{

					SkillManagerInstance.GetSkill(i)->Start();
					ChangeState(SkillManagerInstance.GetSkill(i)->GetFlyState());
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