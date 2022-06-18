#pragma once


#include	"AttackBaseState.h"
#include	"JumpSkill3_1Action.h"
#include	"FixedYInhaleKnockBack.h"

namespace Sample {

	/**
	 * @brief		移動ステート
	 */
	class JumpSkill3_1State : public AttackBaseState
	{
	private:
		/** 移動アクション */
		JumpSkill3_1ActionPtr			m_SkillAction;
		float							m_AttackTime;
		float							m_FinishTime;
		bool							m_ContinueFlg;
		std::string						m_Key;



		const float SkillActionFrameTime = GameFrameTime * 7.0f;

		//1:offset(Vector3) 2:nextHitTime(float) 3:damage(int) 4:knockBack(Vector3)
		//5:collideFlg(bool) 6:type(int) 7:size(Vector3)
		const ShotAABB createShotStatusAABB = { Vector3(0.0f, 0.0f, 0), 0.25f, 0, Vector3(0.5f, 0.15f, 0.5f),false,CHARA_PLAYER,nullptr, Vector3(4.0f, 8.0f, 4.0f) };

		//1:name(string) 2:offset(Vector3) 3:scale(Vector3) 4:rotate(Vector3)
		//5:speed(float)
		const EffectCreateParameter createEffectStatus = { "Effect5", Vector3(0, -1.5f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0, 0.0f),1.8f };

	public:
		/**
		 * @brief		コンストラクタ
		 */
		JumpSkill3_1State()
			: AttackBaseState()
		{
		}


		const KnockBackPtr GetKnockBack() override { return std::make_shared<CFixedYInhaleKnockBack>(Actor()); }
		const ShotAABB& GetCreateShotStatusAABB() override { return createShotStatusAABB; }
		const EffectCreateParameter& GetCreateEffectStatus() override { return createEffectStatus; }

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {
			m_SkillAction = Actor()->GetAction<JumpSkill3_1Action>(GetKey());

			m_AttackTime = 0.0f;
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

			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_SKILL3_1, 0.0f, 0.6f, 0.1f, TRUE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Execution() override {

			
			for (auto& shot : m_pShots)
			{
				shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
				if (m_AttackTime >= SkillActionFrameTime)
				{
					shot->SetCollideFlg(true);
					
				}
				else if (shot->GetCollideFlg())
				{
					shot->SetCollideFlg(false);
				}
			}
			if (m_AttackTime >= SkillActionFrameTime)
			{
				m_AttackTime = 0.0f;
			}
			for (auto& effect : m_pEffects)
			{
				EffectControllerInstance.SetPosition(effect->GetHandle(), Actor()->GetPosition() + createEffectStatus.offset);
			}
			

			m_AttackTime += CUtilities::GetFrameSecond() * TimeControllerInstance.GetTimeScale(Actor()->GetType());

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

			AttackBaseState::Execution();

		}

		/**
		 * @brief		ステート内の入力処理
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
		 * @brief		ステート内の終了処理
		 */
		void End() override {
			m_SkillAction->End();
			AttackBaseState::End();

		}

		/**
		 * @brief		ステート内の接触イベント
		 * @param[in]	type		当たった相手のタイプ
		 * @param[in]	obj			当たった相手のオブジェクト
		 */
		void CollisionEvent(unsigned int type, std::any obj) override {
		}

		/**
		 * @brief		ステートキーの取得
		 */
		const StateKeyType GetKey() const override {
			return STATE_KEY_JUMPSKILL3_1;
		}
	};

}