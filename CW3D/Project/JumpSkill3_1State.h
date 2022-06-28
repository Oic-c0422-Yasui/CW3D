#pragma once


#include	"AttackBaseState.h"
#include	"JumpSkill3_1Action.h"
#include	"FixedYInhaleKnockBack.h"

namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class JumpSkill3_1State : public AttackBaseState
	{
	public:
		struct Parameter
		{
			float SkillActionFrameTime;
			float FinishTime;
			ShotAABB ShotStatus;
			EffectCreateParameter EffectStatus;
		};
	private:
		Parameter m_Parameter;
		/** �ړ��A�N�V���� */
		JumpSkill3_1ActionPtr			m_SkillAction;
		float							m_AttackTime;
		bool							m_ContinueFlg;
		std::string						m_Key;



		const float SkillActionFrameTime = GameFrameTime * 7.0f;


	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		JumpSkill3_1State(Parameter param)
			: AttackBaseState()
			, m_Parameter(param)
			, m_ContinueFlg(false)
			, m_AttackTime(0.0f)
			, m_Key()
		{
		}


		const KnockBackPtr GetKnockBack() override { return std::make_shared<CFixedYInhaleKnockBack>(Actor()); }
		const ShotAABB& GetCreateShotStatusAABB() override { return m_Parameter.ShotStatus; }
		const EffectCreateParameter& GetCreateEffectStatus() override { return m_Parameter.EffectStatus; }

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_SkillAction = Actor()->GetAction<JumpSkill3_1Action>(GetKey());

			m_AttackTime = 0.0f;
			m_ContinueFlg = true;

			AttackBaseState::Start();
			m_SkillAction->Start();

			
			CreateShotAABB();
			CreateEffect();
			for (auto& shot : m_pShots)
			{
				float damage = shot->GetDamage() * (Actor()->GetSkillController()->GetSkill(SKILL_KEY_2)->GetDamage() * 0.01f);
				shot->SetDamage(damage);
			}
			m_Key = Actor()->GetSkillController()->GetSkill(SKILL_KEY_2)->GetButton();

			Vector3 pos(0, 10, -20);
			Vector3 lookPos(0, 3, 0);
			if (Actor()->IsReverse())
			{
				pos.x *= -1;
				lookPos.x *= -1;
			}
			CameraPtr camera;
			camera = std::make_shared<CFollowFixedCamera>(Actor()->GetPosition(), Actor()->GetPosition(), pos, lookPos);
			CameraControllerInstance.SetCamera(camera, 2.3f, MyUtilities::EASE_IN_SINE, 0.7f, MyUtilities::EASE_IN_SINE, 0.5f);

		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {

			
			for (auto& shot : m_pShots)
			{
				shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
				if (m_AttackTime >= m_Parameter.SkillActionFrameTime)
				{
					shot->SetCollideFlg(true);

				}
				else if (shot->GetCollideFlg())
				{
					shot->SetCollideFlg(false);
				}
			}
			if (m_AttackTime >= m_Parameter.SkillActionFrameTime)
			{
				m_AttackTime = 0.0f;
			}
			for (auto& effect : m_pEffects)
			{
				EffectControllerInstance.SetPosition(effect->GetHandle(), Actor()->GetPosition() + m_Parameter.EffectStatus.offset);
			}
			

			m_AttackTime += CUtilities::GetFrameSecond() * TimeControllerInstance.GetTimeScale(Actor()->GetType());

			if (m_CurrentTime > m_Parameter.FinishTime || !m_ContinueFlg)
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

			AttackBaseState::Execution();

		}

		/**
		 * @brief		�X�e�[�g���̓��͏���
		 */
		void InputExecution() override {

			if (m_CurrentTime > 0.5f)
			{
				if (Input()->IsPress(m_Key))
				{
					m_ContinueFlg = true;
				}
				else
				{
					m_ContinueFlg = false;
				}
			}

			if (Input()->IsNegativePress(INPUT_KEY_HORIZONTAL) ||
				Input()->IsPress(INPUT_KEY_HORIZONTAL) ||
				Input()->IsNegativePress(INPUT_KEY_VERTICAL) ||
				Input()->IsPress(INPUT_KEY_VERTICAL))
			{
				m_SkillAction->Acceleration(Input()->GetAxis(INPUT_KEY_HORIZONTAL), -(Input()->GetAxis(INPUT_KEY_VERTICAL)));
			}

			AttackBaseState::InputExecution();
		}



		/**
		 * @brief		�X�e�[�g���̏I������
		 */
		void End() override {
			m_SkillAction->End();
			AttackBaseState::End();
			CameraControllerInstance.SetDefault();
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
			return STATE_KEY_JUMPSKILL3_1;
		}
	};

}