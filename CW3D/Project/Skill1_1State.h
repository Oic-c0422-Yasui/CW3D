#pragma once


#include	"AttackBaseState.h"
#include	"Skill1_1Action.h"
#include	"FixedCamera.h"

namespace Sample {

	/**
	 * @brief		�ړ��X�e�[�g
	 */
	class Skill1_1State : public AttackBaseState
	{
	public:
		struct Parameter : public BaseParam
		{
			float CollideStartFrameTime;
			float CollideEndFrameTime;
			ShotAABB ShotStatus;
			EffectCreateParameter EffectStatus;
		};
	private:
		Parameter m_Parameter;
		/** �ړ��A�N�V���� */
		Skill1_1ActionPtr			m_SkillAction;

		bool collideStartFlg;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		Skill1_1State(Parameter param)
			: AttackBaseState()
			, m_Parameter(param)
			, collideStartFlg(false)
		{
		}


		const ShotAABB& GetCreateShotStatusAABB() override { return m_Parameter.ShotStatus; }
		const EffectCreateParameter& GetCreateEffectStatus() override { return m_Parameter.EffectStatus; }

		/**
		 * @brief		�X�e�[�g���̊J�n����
		 */
		void Start() override {
			m_SkillAction = Actor()->GetAction<Skill1_1Action>(GetKey());
			collideStartFlg = false;
			AttackBaseState::Start();
			m_SkillAction->Start();
			CreateShotAABB();
			CreateEffect();
			for (auto& shot : m_pShots)
			{
				float damage = shot->GetDamage() * (Actor()->GetSkillController()->GetSkill(SKILL_KEY_3)->GetDamage() * 0.01f);
				shot->SetDamage(damage);
			}

			MyUtilities::ANIM_DATA anim[] =
			{
				{0.0f,0.0f},
				{0.8f,0.0f},
				{0.8f,1.0f},
			};
			TimeControllerInstance.SetOtherTimeScale(Actor()->GetType(),anim, _countof(anim));


			MyUtilities::ANIMV3_DATA animPos[] =
			{
				{0.0f,Vector3(-7,2,-2)},
				{0.25f,Vector3(-7,2,-2),MyUtilities::EASE_OUT_SINE},
				{0.30f,Vector3(-25,2,-2),MyUtilities::EASE_OUT_SINE},
			};
			MyUtilities::ANIMV3_DATA animLookPos[] =
			{
				{0.0f,Vector3(2, 1, 2)},
				{1.0f,Vector3(2, 1, 2)},
				{1.0f,Vector3(2, 1, 2)},
			};
			Vector3 pos(-7, 2, -2);
			Vector3 lookPos(2, 1, 2);
			if (Actor()->IsReverse())
			{
				pos.x *= -1;
				lookPos.x *= -1;
				for (int i = 0; i < _countof(animPos); i++)
				{
					animPos[i].Value.x *= -1;
					animLookPos[i].Value.x *= -1;
				}
			}
			CameraPtr camera;
			camera = std::make_shared<CFixedCamera>(Actor()->GetPosition(), Actor()->GetPosition(), pos, lookPos);
			camera->SetAnim(animPos, animLookPos, _countof(animPos));
			CameraControllerInstance.SetCamera(camera,1,MyUtilities::EASE_IN_SINE,0.3f, MyUtilities::EASE_IN_SINE,0.15f);

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
			if (m_CurrentTime >= m_Parameter.CollideStartFrameTime && !collideStartFlg)
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
			return STATE_KEY_SKILL1_1;
		}
	};

}