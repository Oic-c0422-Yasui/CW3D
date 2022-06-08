#pragma once


#include	"AttackBaseState.h"
#include	"Skill1_1Action.h"

namespace Sample {

	/**
	 * @brief		移動ステート
	 */
	class Skill1_1State : public AttackBaseState
	{
	private:
		/** 移動アクション */
		Skill1_1ActionPtr			m_SkillAction;

		const float CollideStartFrameTime = GameFrameTime * 55.0f;
		const float CollideEndFrameTime = GameFrameTime * 80.0f;

		bool collideStartFlg;

		//1:offset(Vector3) 2:nextHitTime(float) 3:damage(int) 4:knockBack(Vector3)
		//5:collideFlg(bool) 6:type(int) 7:size(Vector3)
		const ShotAABB createShotStatusAABB = { Vector3(6.0f, 0.7f, 0), 0.05f, 0, Vector3(0.5f, 0.2f, 0.0f),false,0, nullptr, Vector3(5.0f, 10.0f, 7.0f) };

		//1:name(string) 2:offset(Vector3) 3:scale(Vector3) 4:rotate(Vector3)
		//5:speed(float)
		const EffectCreateParameter createEffectStatus = { "Effect3", Vector3(0.8f, -1.5f, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, MOF_ToRadian(90), 0.0f),1.8f };
	public:
		/**
		 * @brief		コンストラクタ
		 */
		Skill1_1State()
			: AttackBaseState()
		{
		}


		const ShotAABB& GetCreateShotStatusAABB() override { return createShotStatusAABB; }
		const EffectCreateParameter& GetCreateEffectStatus() override { return createEffectStatus; }

		/**
		 * @brief		ステート内の開始処理
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
				float damage = shot->GetDamage() * (Actor()->GetSkillController()->GetSkill(SKILL_KEY_1)->GetDamage() * 0.01f);
				shot->SetDamage(damage);
			}

			Actor()->GetAnimationState()->ChangeMotionByName(STATE_KEY_ATTACK1, 0.0f, 0.6f, 0.1f, FALSE, MOTIONLOCK_OFF, TRUE);
		}

		/**
		 * @brief		ステート内の実行処理
		 */
		void Execution() override {

			for (auto& shot : m_pShots)
			{
				shot->SetPosition(Actor()->GetTransform()->GetPosition() + shot->GetOffset());
				if (m_CurrentTime >= CollideStartFrameTime && !collideStartFlg)
				{
					shot->SetCollideFlg(true);
				}
				if (m_CurrentTime > CollideStartFrameTime)
				{
					if (shot->GetCollideFlg())
					{
						shot->SetCollideFlg(false);
					}
				}

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
		 * @brief		ステート内の入力処理
		 */
		void InputExecution() override {
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
			return STATE_KEY_SKILL1_1;
		}
	};

}