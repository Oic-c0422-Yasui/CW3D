#pragma once


#include	"AttackBaseState.h"
#include	"Skill2_1Action.h"

namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class Skill2_1State : public AttackBaseState
	{
	private:
		/** �ړ��A�N�V���� */
		Skill2_1ActionPtr			m_SkillAction;

		const float CollideStartFrameTime = GameFrameTime * 15.0f;
		const float CollideEndFrameTime = GameFrameTime * 25.0f;

		bool collideStartFlg;

		//1:offset(Vector3) 2:nextHitTime(float) 3:damage(int) 4:knockBack(Vector3)
		//5:collideFlg(bool) 6:type(int) 7:size(Vector3)
		const ShotAABB createShotStatusAABB = { Vector3(6.0f, 0.7f, 0), 0.0f, 0, Vector3(0.5f, 0.2f, 0.0f),false,CHARA_PLAYER, nullptr, Vector3(5.0f, 2.0f, 2.0f) };

		//1:offset(Vector3) 2:nextHitTime(float) 3:damage(int) 4:knockBack(Vector3)
		//5:collideFlg(bool) 6:type(int) 7:radius(float)
		const ShotSphere createShotStatusSphere = { Vector3(0.7f, 0.7f, 0), 0.1f, 0, Vector3(0.5f, 0.2f, 0.0f),false,CHARA_PLAYER, nullptr,2.0f };

		ShotSphere m_ShotStatusSphere;

		//1:name(string) 2:offset(Vector3) 3:scale(Vector3) 4:rotate(Vector3)
		//5:speed(float)
		const EffectCreateParameter createEffectStatus = { "Effect4", Vector3(1.7f, 1.2f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, MOF_ToRadian(90), 0.0f),1.2f };

		EffectCreateParameter m_EffectStatus;
	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Skill2_1State()
			: AttackBaseState()
		{
		}

		const ShotAABB& GetCreateShotStatusAABB() override { return createShotStatusAABB; }
		const ShotSphere& GetCreateShotStatusSphere() override { return m_ShotStatusSphere; }
		const EffectCreateParameter& GetCreateEffectStatus() override { return m_EffectStatus; }

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_SkillAction = Actor()->GetAction<Skill2_1Action>(GetKey());

			AttackBaseState::Start();
			collideStartFlg = false;
			m_SkillAction->Start();

			m_EffectStatus = createEffectStatus;
			m_ShotStatusSphere = createShotStatusSphere;
			if (Input()->IsNegativePress(INPUT_KEY_VERTICAL))
			{
				float rad = MOF_ToRadian(-30);
				Vector3 direction(cos(rad), sin(rad), 0);
				int shotCount = 3;
				for (int i = 0; i < shotCount; i++)
				{
					m_ShotStatusSphere.offset = Vector3(((2 + (4 * i)) * direction.x), 0.7f + -((2 + (4 * i)) * direction.y), 0);
					CreateShotSphere();
				}

				m_EffectStatus.offset = Vector3(1.7f, 1.8f, 0);
				m_EffectStatus.rotate = Vector3(MOF_ToRadian(-30), MOF_ToRadian(90), 0);
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

			

			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_SKILL2_1, 0.7f, 2.0f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		�X�e�[�g���̎��s����
		 */
		void Execution() override {

			for (auto& shot : m_pShots)
			{
				shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
				if (m_CurrentTime >= CollideStartFrameTime && !collideStartFlg)
				{
					shot->SetCollideFlg(true);
				}
				if (m_CurrentTime > CollideEndFrameTime)
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
			if (m_CurrentTime >= CollideStartFrameTime && !collideStartFlg)
			{
				collideStartFlg = true;
			}
			


			if (Actor()->GetAnimationState()->IsEndMotion())
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
			return STATE_KEY_SKILL2_1;
		}
	};

}