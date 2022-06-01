#pragma once


#include	"State.h"
#include	"Attack2Action.h"

namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class Attack2State : public State
	{
	private:
		/** �ړ��A�N�V���� */
		Attack2ActionPtr			m_Attack2Action;
		bool						m_NextInputFlg;
		int							m_FrameTime;
		std::vector<ShotPtr>		m_Shots;
		EffectPtr					m_Effect;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Attack2State()
			: State()
			, m_NextInputFlg(false)
			, m_FrameTime(0)
		{
		}
		const ShotAABB createShotStatus = { Vector3(0.7f, 0.7f, 0), 0.5f, 0, 0, Vector3(0.8f, 1.5f, 0.8f) };

		virtual const ShotAABB& GetCreateShotStatus() {
			return createShotStatus;
		}

		virtual void CreateShot()
		{
			auto& attack = Actor()->GetParameterMap()->Get<int>(PARAMETER_KEY_ATTACK);
			ShotAABB status = GetCreateShotStatus();
			status.damage += attack;
			if (Actor()->IsReverse())
			{
				status.offset.x *= -1;
			}

			m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), status));
		}

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_Attack2Action = Actor()->GetAction<Attack2Action>(GetKey());
			m_FrameTime = 0;
			m_NextInputFlg = false;
			m_Attack2Action->Start();
			CreateShot();

			auto& attack = Actor()->GetParameterMap()->Get<int>(PARAMETER_KEY_ATTACK);
			if (Actor()->IsReverse())
			{
				m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), Vector3(-0.7f, 0.7f, 0), 0.8f, attack, 0));

			}
			else
			{
				m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), Vector3(0.7f, 0.7f, 0), 0.8f, attack, 0));
			}
			auto& attack = Actor()->GetParameterMap()->Get<int>(PARAMETER_KEY_ATTACK);
			ShotAABB status = createShotStatus;
			status.damage += attack;
			if (Actor()->IsReverse())
			{
				status.offset.x *= -1;
			}

			m_Shots.push_back(ShotManagerInstance.Create(Actor()->GetPosition(), status));
			for (auto& shot : m_Shots)
			{
				shot->SetCollideFlg(false);
				shot->SetKnockBackX(0.2f);
			}
			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_ATTACK2, 0.0f, 1.0f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {

			for (auto& shot : m_Shots)
			{
				shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
				if (m_FrameTime == 25)
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
				ChangeState(STATE_KEY_IDLE);
			}
			if (m_NextInputFlg)
			{
				if (m_FrameTime > 40)
				{
					ChangeState(STATE_KEY_ATTACK3);
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
				if (!Actor()->GetSkillController()->GetSkill(i)->GetCanUseFlg() || Actor()->GetSkillController()->GetSkill(i)->GetState() == NULL)
				{
					continue;
				}
				if (Input()->IsPush(Actor()->GetSkillController()->GetSkill(i)->GetButton()))
				{

					Actor()->GetSkillController()->GetSkill(i)->Start();
					ChangeState(Actor()->GetSkillController()->GetSkill(i)->GetState());
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
			return STATE_KEY_ATTACK2;
		}
	};

}