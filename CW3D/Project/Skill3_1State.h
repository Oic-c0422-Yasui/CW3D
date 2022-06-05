#pragma once


#include	"AttackBaseState.h"
#include	"Skill3_1Action.h"

namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class Skill3_1State : public AttackBaseState
	{
	private:
		/** �ړ��A�N�V���� */
		Skill3_1ActionPtr			m_SkillAction;
		float						m_CurrentTime;
		float						m_FinishTime;
		bool						m_ContinueFlg;
		std::string					m_Key;

		//1:offset(Vector3) 2:nextHitTime(float) 3:damage(int) 4:knockBack(Vector3)
		//5:collideFlg(bool) 6:type(int) 7:size(Vector3)
		const ShotAABB createShotStatusAABB = { Vector3(0.0f, 0.0f, 0), 0.1f, 0, Vector3(-0.1f, 0.1f, 0.0f),false,0, Vector3(4.0f, 8.0f, 4.0f) };

		//1:name(string) 2:offset(Vector3) 3:scale(Vector3) 4:rotate(Vector3)
		//5:speed(float)
		const EffectCreateParameter createEffectStatus = { "Effect5", Vector3(0, 0, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0, 0.0f),1.8f };

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Skill3_1State()
			: AttackBaseState()
		{
		}

		const ShotAABB& GetCreateShotStatusAABB() override { return createShotStatusAABB; }
		const EffectCreateParameter& GetCreateEffectStatus() override { return createEffectStatus; }

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_SkillAction = Actor()->GetAction<Skill3_1Action>(GetKey());

			m_CurrentTime = 0.0f;
			m_FinishTime = 3.5f;
			m_ContinueFlg = true;

			AttackBaseState::Start();
			m_SkillAction->Start();
			CreateShotAABB();
			CreateEffect();
			for (auto& shot : m_pShots)
			{
				float damage = shot->GetDamage() * (Actor()->GetSkillController()->GetSkill(SKILL_KEY_3)->GetDamage() * 0.01f);
				shot->SetDamage(damage);
			}

			for (int i = 0; i < Actor()->GetSkillController()->GetCount(); i++)
			{
				if (Actor()->GetSkillController()->GetSkill(i)->GetState() != STATE_KEY_SKILL3_1)
				{
					continue;
				}

				m_Key = Actor()->GetSkillController()->GetSkill(i)->GetButton();
				break;
			}

			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_SKILL3_1, 0.0f, 0.6f, 0.1f, TRUE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {

			for (auto& shot : m_pShots)
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

			for (auto& effect : m_pEffects)
			{
				EffectControllerInstance.SetPosition(effect->GetHandle(), Actor()->GetPosition() + createEffectStatus.offset);
			}

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
			return STATE_KEY_SKILL3_1;
		}
	};

}