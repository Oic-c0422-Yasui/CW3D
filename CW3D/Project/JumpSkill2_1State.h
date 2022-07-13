#pragma once


#include	"AttackBaseState.h"
#include	"JumpSkill2_1Action.h"
#include	"AdditionalSkill.h"


namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class JumpSkill2_1State : public AttackBaseState
	{
	public:
		struct Parameter : public BaseParam
		{
			float CollideStartFrameTime;
			float CollideEndFrameTime;
			ShotAABB AABBShotStatus;
			ShotSphere SphereShotStatus;
			EffectCreateParameter EffectStatus;
		};
	private:
		Parameter m_Parameter;
		/** �ړ��A�N�V���� */
		JumpSkill2_1ActionPtr			m_SkillAction;

		bool collideStartFlg;

		bool m_DelayInputFlg;

		ShotSphere m_ShotStatusSphere;

		EffectCreateParameter m_EffectStatus;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		JumpSkill2_1State(Parameter param)
			: AttackBaseState()
			, m_Parameter(param)
			, collideStartFlg(false)
			, m_DelayInputFlg(false)
		{
		}
		const ShotAABB& GetCreateShotStatusAABB() override { return m_Parameter.AABBShotStatus; }
		const ShotSphere& GetCreateShotStatusSphere() override { return m_ShotStatusSphere; }
		const EffectCreateParameter& GetCreateEffectStatus() override { return m_EffectStatus; }

		

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_SkillAction = Actor()->GetAction<JumpSkill2_1Action>(GetKey());
			Initialize();
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {

			for (auto& shot : m_pShots)
			{
				shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
				if (m_CurrentTime >= m_Parameter.CollideStartFrameTime && !collideStartFlg)
				{
					shot->SetCollideFlg(true);
				}
				if (m_CurrentTime > m_Parameter.CollideEndFrameTime)
				{
					if (shot->GetCollideFlg())
					{
						shot->SetCollideFlg(false);
					}
				}

			}
			for (auto& effect : m_pEffects)
			{
				EffectControllerInstance.SetPosition(effect->GetHandle(), Actor()->GetPosition() + effect->GetOffset());
			}
			if (m_CurrentTime >= m_Parameter.CollideStartFrameTime && !collideStartFlg)
			{
				collideStartFlg = true;
			}

			if (Actor()->GetAnimationState()->IsEndMotion())
			{
				if (m_NextInputFlg)
				{
					for (auto& shot : m_pShots)
					{
						shot->SetShow(false);
					}
					Initialize();
				}
				else
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
			AttackBaseState::Execution();
		}

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		void InputExecution() override {
			AttackBaseState::InputExecution();
		}



		/**
		 * @brief		�X�e�[�g���̏I������
		 */
		void End() override {
			m_SkillAction->End();
			AttackBaseState::End();
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
			return STATE_KEY_JUMPSKILL2_1;
		}


		void Initialize()
		{

			AttackBaseState::Start();
			m_SkillAction->Start();
			collideStartFlg = false;
			m_EffectStatus = m_Parameter.EffectStatus;
			m_ShotStatusSphere = m_Parameter.SphereShotStatus;

			if (Input()->IsPress(INPUT_KEY_VERTICAL))
			{

				float rad = MOF_ToRadian(-30);
				Vector3 direction(cos(rad), sin(rad), 0);
				int shotCount = 3;
				for (int i = 0; i < shotCount; i++)
				{
					m_ShotStatusSphere.offset = Vector3(((2 + (4 * i)) * direction.x), 0.7f + ((2 + (4 * i)) * direction.y), 0);
					CreateShotSphere();
				}

				m_EffectStatus.offset = Vector3(1.7f, 0.7f, 0);
				m_EffectStatus.rotate = Vector3(MOF_ToRadian(30), MOF_ToRadian(90), 0);
				CreateEffect();

			}
			else
			{
				CreateShotAABB();
				CreateEffect();

			}
			for (auto& shot : m_pShots)
			{
				float damage = shot->GetDamage() * (Actor()->GetSkillController()->GetSkill(SKILL_KEY_2)->GetDamage() * 0.01f);
				shot->SetDamage(damage);
			}
		}
	};

}