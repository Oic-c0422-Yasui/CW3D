#pragma once


#include	"AttackBaseState.h"
#include	"Skill3_1Action.h"
#include	"FixedYInhaleKnockBack.h"
#include	"FollowFixedCamera.h"

namespace Sample {

	/**
	 * @brief		移動ステート
	 */
	class Skill3_1State : public AttackBaseState
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
		/** 移動アクション */
		Skill3_1ActionPtr			m_SkillAction;
		float						m_AttackTime;

		bool						m_ContinueFlg;
		std::string					m_Key;

		const float SkillActionFrameTime = GameFrameTime * 7.0f;

		//1:offset(Vector3) 2:nextHitTime(float) 3:damage(int) 4:knockBack(Vector3)
		//5:collideFlg(bool) 6:type(int) 7:size(Vector3)
		const ShotAABB createShotStatusAABB = { Vector3(0.0f, 0.0f, 0), 0.25f, 0, Vector3(0.5f, 0.15f, 0.5f),false,CHARA_PLAYER, nullptr, Vector3(4.0f, 8.0f, 4.0f) };

		//1:name(string) 2:offset(Vector3) 3:scale(Vector3) 4:rotate(Vector3)
		//5:speed(float)
		const EffectCreateParameter createEffectStatus = { "Effect5", Vector3(0, 0, 0), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0, 0.0f),1.8f };

	public:
		/**
		 * @brief		コンストラクタ
		 */
		Skill3_1State(Parameter param)
			: AttackBaseState()
			, m_Parameter(param)
			, m_ContinueFlg(false)
			, m_AttackTime(0.0f)
		{
		}


		const KnockBackPtr GetKnockBack() override { return std::make_shared<CFixedYInhaleKnockBack>(Actor()); }
		const ShotAABB& GetCreateShotStatusAABB() override { return m_Parameter.ShotStatus; }
		const EffectCreateParameter& GetCreateEffectStatus() override { return m_Parameter.EffectStatus; }

		/**
		 * @brief		ステート内の開始処理
		 */
		void Start() override {
			m_SkillAction = Actor()->GetAction<Skill3_1Action>(GetKey());

			m_AttackTime = 0.0f;
			//3.5

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
		 * @brief		ステート内の実行処理
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
				EffectControllerInstance.SetPosition(effect->GetHandle(), Actor()->GetPosition() + createEffectStatus.offset);
			}

			m_AttackTime += CUtilities::GetFrameSecond();

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
			CameraControllerInstance.SetDefault();

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
			return STATE_KEY_SKILL3_1;
		}
	};

}